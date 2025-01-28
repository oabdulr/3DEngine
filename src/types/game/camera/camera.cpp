#include "camera.h"

void camera::event_input(int event_type, SDL_Event event) {
    switch (event_type){
        case SDL_KEYDOWN:
            if (this->assert_key("forward", event.key.keysym.scancode))
                this->Transform.position += this->looking_direction * 0.5f;
            else if (this->assert_key("back", event.key.keysym.scancode))
                this->Transform.position -= this->looking_direction * 0.5f;
            else if (this->assert_key("left", event.key.keysym.scancode))
                this->Transform.position -= this->right * 0.5f;
            else if (this->assert_key("right", event.key.keysym.scancode))
                this->Transform.position += this->right * 0.5f;
            break;
        case SDL_MOUSEMOTION:
            this->yaw += 0.001f * event.motion.xrel;
            break;
        default:
            break;    
    }
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

void camera::render(std::unordered_map<std::string, gameobject*> &objs){
    for (auto &pair_obj : objs){
        std::string tag = pair_obj.first;
        gameobject* obj = pair_obj.second;
        if (obj == this) continue;

        matrix4x4 mm =  matrix4x4::translate(obj->Transform.position)
                      * matrix4x4::rotateY(obj->Transform.rotation.y)
                      * matrix4x4::scale(obj->Bounds.scale);

        matrix4x4 mvm = this->proj_matrix * this->view_matrix * mm;

        static std::vector<vec3> screenVertices {};
        screenVertices.clear();
        
        for (const vec3& vertex : obj->Bounds.VERTEX) {
            vec4 v = vec4(vertex.x, vertex.y, vertex.z, 1.0f);
            vec4 transformedVertex = v * mvm;

            if (transformedVertex.w != 0.0f) {
                transformedVertex.x /= transformedVertex.w;
                transformedVertex.y /= transformedVertex.w;
                transformedVertex.z /= transformedVertex.w;
            }

            float screenX = (transformedVertex.x + 1.0f) * 0.5f * this->pWinSize->w;
            float screenY = (1.0f - transformedVertex.y) * 0.5f * this->pWinSize->h; // Flip Y for screen coordinates


            screenVertices.push_back({screenX, screenY, transformedVertex.z});

        }

        for (auto& edge : obj->Bounds.EDGES) {
            vec3& start = screenVertices[edge.first];
            vec3& end = screenVertices[edge.second];

            bool startx_out = start.x > this->pWinSize->w || start.x < 0;
            bool endx_out = end.x > this->pWinSize->w || end.x < 0;

            bool starty_out = start.y > this->pWinSize->h || start.y < 0;
            bool endy_out = end.y > this->pWinSize->h || end.y < 0;

            if (start.z < 0.0f || end.z < 0.0f)
                continue;
            if ((startx_out && endx_out) ||
                (starty_out && endy_out))
                continue;            

            this->pDrawing->render_line(start, end);
        }

    }
}