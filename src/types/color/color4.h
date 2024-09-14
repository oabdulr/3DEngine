#pragma once
#include <pch.h>

class color4 : public vec4{
public:
    float r, g, b, alpha;
    color4(float r, float g, float b, float alpha) : r(r), g(g), b(b), alpha(alpha), vec4(r, g, b, alpha) {}
    color4(float r, float g, float b) : r(r), g(g), b(b), alpha(255), vec4(r, g, b, 255) {}

    void convert_to_idk(){
        this->x /= 255;
        this->y /= 255;
        this->z /= 255;
        this->w /= 255;
    }

    operator SDL_Color () const{
        return { (Uint8)this->r, (Uint8)this->g, (Uint8)this->b, (Uint8)this->alpha };
    }

    std::string to_string(){
        return std::to_string(this->r) + std::to_string(this->g) + std::to_string(this->b) + std::to_string(this->alpha);
    }
};