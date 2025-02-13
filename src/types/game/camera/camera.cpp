#include "camera.h"
#include <xmmintrin.h>  // SSE intrinsics
#include <emmintrin.h>  // SSE2 intrinsics

void camera::event_input(int event_type, SDL_Event event) {
    switch (event_type){
        case SDL_KEYMAPCHANGED:
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            if (this->assert_key("forward", event.key.keysym.scancode))
                this->Transform.position += this->looking_direction;
            if (this->assert_key("back", event.key.keysym.scancode))
                this->Transform.position -= this->looking_direction;
            if (this->assert_key("left", event.key.keysym.scancode))
                this->Transform.position -= this->right;
            if (this->assert_key("right", event.key.keysym.scancode))
                this->Transform.position += this->right;
            if (this->assert_key("view_up", event.key.keysym.scancode))
                this->pitch += 0.1f;
            if (this->assert_key("view_down", event.key.keysym.scancode))
                this->pitch -= 0.1f;
            if (this->assert_key("view_left", event.key.keysym.scancode))
                this->yaw -= 0.1f;
            if (this->assert_key("view_right", event.key.keysym.scancode))
                this->yaw += 0.1f;
            break;
        case SDL_MOUSEMOTION:
            break;
        default:
            break;    
    }
}

static inline float edge_function(const vec2& a, const vec2& b, const vec2& c) {
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}


void camera::set_fov(float fov){
    this->fov = fov;
    this->rad_fov = this->fov * this->radians;
}

void camera::rotate(float y, float p, bool set){
    if (set){
        this->yaw = y;
        this->pitch = p;
        return;
    }

    this->yaw += y;
    this->pitch += p;
}

void camera::update(){
    this->looking_direction = vec3(cos(this->pitch) * cos(this->yaw), 
                                   sin(this->pitch),
                                   cos(this->pitch) * sin(this->yaw));

    this->right = this->looking_direction.cross(vec3(0.0f, 1.0f, 0.0f));
    this->up = this->right.cross(this->looking_direction);

    this->looking_direction = this->looking_direction.normalize();
    this->right = this->right.normalize();
    this->up = this->up.normalize();
    
    vec3 target = this->Transform.position + this->looking_direction;
    this->view_matrix = matrix4x4::lookAt(this->Transform.position, target, this->up);
    
    float aspect_ratio = this->pWinSize->w / this->pWinSize->h;
    this->proj_matrix = matrix4x4::perspective(this->rad_fov, aspect_ratio, this->near_plane, this->far_plane);
}


void camera::render(std::unordered_map<std::string, gameobject*> &objs) {
    const int bufferWidth  = this->pWinSize->w;
    const int bufferHeight = this->pWinSize->h;
    const size_t bufferSize = bufferWidth * bufferHeight;

    this->z_buffer.assign(bufferSize, 1.0f);

    for (auto &pair_obj : objs) {
        gameobject* obj = pair_obj.second;
        if (obj == this) continue;

        matrix4x4 mm = matrix4x4::translate(obj->Transform.position)
                      * matrix4x4::rotateY(obj->Transform.rotation.y)
                      * matrix4x4::scale(obj->Bounds.scale);

        matrix4x4 mvm = this->proj_matrix * this->view_matrix * mm;

        std::vector<vec4> screenVertices;
        screenVertices.reserve(obj->Bounds.VERTEX.size());
        for (const vec3& vertex : obj->Bounds.VERTEX) {
            vec4 v(vertex.x, vertex.y, vertex.z, 1.0f);
            vec4 transformedVertex = v * mvm;

            if (transformedVertex.w == 0.0f) continue;
            float invW = 1.0f / transformedVertex.w;
            transformedVertex.x *= invW;
            transformedVertex.y *= invW;
            transformedVertex.z *= invW;

            float screenX = (transformedVertex.x + 1.0f) * 0.5f * bufferWidth;
            float screenY = (1.0f - transformedVertex.y) * 0.5f * bufferHeight;

            screenVertices.emplace_back(screenX, screenY, transformedVertex.z, invW);
        }

        this->pDrawing->set_draw_color(obj->col);

        for (const auto& face : obj->Bounds.FACES) {
            const int idx0 = std::get<0>(face);
            const int idx1 = std::get<1>(face);
            const int idx2 = std::get<2>(face);

            const vec4& v0 = screenVertices[idx0];
            const vec4& v1 = screenVertices[idx1];
            const vec4& v2 = screenVertices[idx2];

            if (v0.z <= 0 || v1.z <= 0 || v2.z <= 0) continue;

            int minX = std::max(0, static_cast<int>(std::floor(std::min({v0.x, v1.x, v2.x}))));
            int maxX = std::min(bufferWidth - 1, static_cast<int>(std::ceil (std::max({v0.x, v1.x, v2.x}))));
            int minY = std::max(0, static_cast<int>(std::floor(std::min({v0.y, v1.y, v2.y}))));
            int maxY = std::min(bufferHeight - 1, static_cast<int>(std::ceil (std::max({v0.y, v1.y, v2.y}))));


            auto computeEdgeCoeffs = [](const vec4 &a, const vec4 &b) -> std::tuple<float, float, float> {
                float A = b.y - a.y;
                float B = -(b.x - a.x);
                float C = -(A * a.x + B * a.y);
                return {A, B, C};
            };

            float A0, B0, C0;
            std::tie(A0, B0, C0) = computeEdgeCoeffs(v1, v2);
            float A1, B1, C1;
            std::tie(A1, B1, C1) = computeEdgeCoeffs(v2, v0);
            float A2, B2, C2;
            std::tie(A2, B2, C2) = computeEdgeCoeffs(v0, v1); 

            float area = A2 * v2.x + B2 * v2.y + C2;
            if (area <= 0) continue;

            for (int y = minY; y <= maxY; ++y) {
                float px = minX + 0.5f;
                float py = y + 0.5f;
                float w0 = A0 * px + B0 * py + C0;
                float w1 = A1 * px + B1 * py + C1;
                float w2 = A2 * px + B2 * py + C2;

                const float stepX0 = A0;
                const float stepX1 = A1;
                const float stepX2 = A2;

                for (int x = minX; x <= maxX; ++x) {
                    if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                        float alpha = w0 / area;
                        float beta  = w1 / area;
                        float gamma = w2 / area;

                        float interpolated_rcp_w = alpha * v0.w + beta * v1.w + gamma * v2.w;
                        if (interpolated_rcp_w != 0.0f) {
                            float interpolated_z = (alpha * v0.z * v0.w +
                                                    beta  * v1.z * v1.w +
                                                    gamma * v2.z * v2.w) / interpolated_rcp_w;
                            int index = y * bufferWidth + x;
                            if (interpolated_z < this->z_buffer[index]) {
                                this->z_buffer[index] = interpolated_z;
                                this->pDrawing->render_pixel({ (float)x, (float)y });
                            }
                        }
                    }

                    w0 += stepX0;
                    w1 += stepX1;
                    w2 += stepX2;
                }
            }
        }
    }
}