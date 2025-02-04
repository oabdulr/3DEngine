#include "camera.h"

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
    const int bufferWidth = this->pWinSize->w;
    const int bufferHeight = this->pWinSize->h;
    const size_t bufferSize = bufferWidth * bufferHeight;

    this->z_buffer = std::vector<float>(bufferSize, 1.0f);

    for (auto &pair_obj : objs) {
        std::string tag = pair_obj.first;
        gameobject* obj = pair_obj.second;
        if (obj == this) continue;

        matrix4x4 mm = matrix4x4::translate(obj->Transform.position)
                      * matrix4x4::rotateY(obj->Transform.rotation.y)
                      * matrix4x4::scale(obj->Bounds.scale);

        matrix4x4 mvm = this->proj_matrix * this->view_matrix * mm;

        std::vector<vec4> screenVertices;
        screenVertices.reserve(obj->Bounds.VERTEX.size());
        
        for (const vec3& vertex : obj->Bounds.VERTEX) {
            vec4 v = vec4(vertex.x, vertex.y, vertex.z, 1.0f);
            vec4 transformedVertex = v * mvm;

            float w_clip = transformedVertex.w;
            if (w_clip == 0.0f) continue;

            float rcp_w = 1.0f / w_clip;
            transformedVertex.x *= rcp_w;
            transformedVertex.y *= rcp_w;
            transformedVertex.z *= rcp_w;

            float screenX = (transformedVertex.x + 1.0f) * 0.5f * bufferWidth;
            float screenY = (1.0f - transformedVertex.y) * 0.5f * bufferHeight;

            screenVertices.emplace_back(screenX, screenY, transformedVertex.z, rcp_w);
        }

        this->pDrawing->set_draw_color(obj->col);
        for (const auto& face : obj->Bounds.FACES) {
            const vec4& v0 = screenVertices[std::get<0>(face)];
            const vec4& v1 = screenVertices[std::get<1>(face)];
            const vec4& v2 = screenVertices[std::get<2>(face)];

            if (v0.z <= 0 || v1.z <= 0 || v2.z <= 0) continue;

            float minX = std::floor(std::min({v0.x, v1.x, v2.x}));
            float maxX = std::ceil(std::max({v0.x, v1.x, v2.x}));
            float minY = std::floor(std::min({v0.y, v1.y, v2.y}));
            float maxY = std::ceil(std::max({v0.y, v1.y, v2.y}));

            minX = std::max(0.f, minX);
            maxX = std::min(bufferWidth - 1.f, maxX);
            minY = std::max(0.f, minY);
            maxY = std::min(bufferHeight - 1.f, maxY);

            vec2 a(v0.x, v0.y);
            vec2 b(v1.x, v1.y);
            vec2 c(v2.x, v2.y);
            float area = edge_function(a, b, c);
            if (area <= 0) continue;

            for (float y = minY; y <= maxY; ++y) {
                for (float x = minX; x <= maxX; ++x) {
                    vec2 pt(x + 0.5f, y + 0.5f);
                    float w0 = edge_function(b, c, pt);
                    float w1 = edge_function(c, a, pt);
                    float w2 = edge_function(a, b, pt);

                    if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                        float alpha = w0 / area;
                        float beta = w1 / area;
                        float gamma = w2 / area;

                        float interpolated_rcp_w = alpha * v0.w + beta * v1.w + gamma * v2.w;
                        if (interpolated_rcp_w == 0.0f) continue;

                        float interpolated_z = (alpha * v0.z * v0.w + beta * v1.z * v1.w + gamma * v2.z * v2.w) / interpolated_rcp_w;

                        int index = y * bufferWidth + x;
                        if (interpolated_z < this->z_buffer[index]) {
                            this->z_buffer[index] = interpolated_z;
                            this->pDrawing->render_pixel({x, y});
                        }
                    }
                }
            }
        }
    }
}