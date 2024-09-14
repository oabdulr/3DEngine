#pragma once
#include <pch.h>

class color4 : public vec4{
public:
    float r, g, b, alpha;
    color4(float r, float g, float b, float alpha) : r(r), g(g), b(b), alpha(alpha), vec4(r, g, b, alpha) {}

    void convert_to_idk(){
        this->x /= 255;
        this->y /= 255;
        this->z /= 255;
        this->w /= 255;
    }
};