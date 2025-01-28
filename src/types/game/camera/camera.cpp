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
    
    static vec3 cameraPosition = {0.0f, 0.0f, 5.0f};
    cameraPosition += {0.0f, 0.0f, 0.001f};
    static vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
    cameraTarget += {0.01f, 0.0f, 0.0f};
    if (cameraTarget.x >= 99.99f)
        cameraTarget.x = 0.f;

    vec3 upVector = {0.0f, 1.0f, 0.0f};

    matrix4x4 viewMatrix = matrix4x4::lookAt(cameraPosition, cameraTarget, upVector);

    // Projection setup
    float fieldOfView = 45.0f * (3.14159265f / 180.0f); // Convert to radians
    float aspectRatio = 1280.0f / 720.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    matrix4x4 projectionMatrix = matrix4x4::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    
    for (auto &pair_obj : objs){
        std::string tag = pair_obj.first;
        gameobject* obj = pair_obj.second;

        // Set up cube transformation
        vec3 objectPosition = {0.0f, 0.0f, 0.0f};
        static float rotationAngle = 0.0f; // in radians
        vec3 objectScale = {1.0f, 1.0f, 1.0f};
        rotationAngle += 0.001;

        matrix4x4 modelMatrix = matrix4x4::translate(objectPosition)
                            * matrix4x4::rotateY(rotationAngle)
                            * matrix4x4::scale(objectScale);

        // Combine to form the MVP matrix
        matrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

        std::vector<vec2> screenVertices;
        
        // Transform each vertex and convert to screen space
        for (const vec3& vertex : obj->Bounds.VERTEX) {
            vec4 v = vec4(vertex.x, vertex.y, vertex.z, 1.0f);
            vec4 transformedVertex = v * mvpMatrix;

            // Perform perspective divide
            if (transformedVertex.w != 0.0f) {
                transformedVertex.x /= transformedVertex.w;
                transformedVertex.y /= transformedVertex.w;
                transformedVertex.z /= transformedVertex.w;
            }

            // Convert from NDC to screen space
            float screenX = (transformedVertex.x + 1.0f) * 0.5f * this->pWinSize->w;
            float screenY = (1.0f - transformedVertex.y) * 0.5f * this->pWinSize->h; // Flip Y for screen coordinates
            screenVertices.push_back({screenX, screenY});

        }

        // Draw lines for each edge of the cube
        for (const auto& edge : obj->Bounds.EDGES) {
            const vec2& start = screenVertices[edge.first];
            const vec2& end = screenVertices[edge.second];
            this->pDrawing->render_line(start, end);
        }

    }
}