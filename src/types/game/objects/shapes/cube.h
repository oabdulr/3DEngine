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

    }
};