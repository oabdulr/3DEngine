#pragma once
#include <pch.h>


class rect : public vec4 {
public:
    float w, h = 0;
    
    rect() {}
    rect(float x, float y, float w, float h) : w(w), h(h), vec4(x, y, w, h) {}

    operator SDL_Rect () const {
        return {(int)x, (int)y, (int)w, (int)h};
    }

    bool is_inside( vec3 position )
    {
        if ( this->x > position.x || this->y > position.y || this->z > position.z)
            return false;
        if ( this->x + this->w < position.x || this->y + this->w < position.y || this->z + this->h < position.z )
            return false;

        return true;
    }
};