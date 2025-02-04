#pragma once
#include <pch.h>

class cube : public gameobject{
public:
    cube(){
        this->Bounds.VERTEX =
            { 
                vec3{ -1.0f, -1.0f, -1.0f}, vec3{ -1.0f, -1.0f, 1.0f }, 
                vec3{ 1.0f, -1.0f, -1.0f}, vec3{ -1.0f, 1.0f, -1.0f},
                vec3{ -1.0f, 1.0f, 1.0f}, vec3{ 1.0f, -1.0f, 1.0f},
                vec3{ 1.0f, 1.0f, -1.0f}, vec3{ 1.0f, 1.0f, 1.0f }
            };

        this->Bounds.EDGES =
            { 
                {0, 1}, {0, 2}, {0, 3},
                {2, 5}, {3, 6}, {3, 4},
                {4, 7}, {6, 7}, {7, 5},
                {5, 1}, {4, 1}, {2, 6}
            };
        this->Bounds.FACES = 
            {
                {0, 1, 5}, {0, 5, 2}, // Bottom face
                {3, 6, 7}, {3, 7, 4}, // Top face
                {0, 3, 4}, {0, 4, 1}, // Left face
                {2, 5, 7}, {2, 7, 6}, // Right face
                {0, 2, 6}, {0, 6, 3}, // Front face
                {1, 4, 7}, {1, 7, 5}  // Back face
            };
    }

    ~cube(){
        
    }
};