#include "camera.h"

vec2 camera::w2s(vec3 pos, float scale){
    // Ensure z is positive to avoid division by zero or negative scaling
    float z = std::max(pos.z, 0.1f);

    return vec2(((this->fov * pos.x) / (this->fov + z)) * scale,
                ((this->fov * pos.y) / (this->fov + z)) * scale);
}

void camera::render(std::unordered_map<std::string, gameobject*> &objs){
    for (auto &pair_obj : objs){
        std::string tag = pair_obj.first;
        gameobject* obj = pair_obj.second;

        for (std::pair<int, int> edge : obj->Bounds.EDGES) {
            // Rotate the vertices using the quaternion
            vec3 Start = obj->Bounds.position + (obj->Bounds.VERTEX[edge.first] * obj->Bounds.scale);
            vec3 End = obj->Bounds.position + (obj->Bounds.VERTEX[edge.second] * obj->Bounds.scale);

            // Convert the world vertices to screen coordinates
            vec2 screenStart = this->w2s(Start);
            vec2 screenEnd = this->w2s(End);
            
            this->pDrawing->render_line(screenStart, screenEnd);
        }
    }
}