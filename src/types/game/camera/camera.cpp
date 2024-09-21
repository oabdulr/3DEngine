#include "camera.h"

vec2 camera::w2s(vec3 pos, float scale){
    // Ensure z is positive to avoid division by zero or negative scaling
    float z = std::max(pos.z, 0.1f);

    // Apply perspective projection
    float factor = this->fov / (this->fov + z);
    return vec2(
        (pos.x * factor) * scale,
        (pos.y * factor) * scale
    );
}

void camera::render(std::unordered_map<std::string, gameobject*> &objs){
    for (auto &pair_obj : objs){
        std::string tag = pair_obj.first;
        gameobject* obj = pair_obj.second;

        for (std::pair<int, int> edge : obj->Bounds.EDGES) {
            vec3 Start = obj->Bounds.VERTEX[edge.first] * obj->Bounds.scale;
            vec3 End = obj->Bounds.VERTEX[edge.second] * obj->Bounds.scale;
            
            Start = obj->Transform.rotation * Start;
            End = obj->Transform.rotation * End;

            Start += obj->Bounds.position;
            End += obj->Bounds.position;

            vec2 screenStart = this->w2s(Start);
            vec2 screenEnd = this->w2s(End);

            this->pDrawing->render_line(screenStart, screenEnd);
        }
    }
}