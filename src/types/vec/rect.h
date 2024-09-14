#pragma once
#include <pch.h>


class rect : public vec4 {
public:
    float w, h = 0;
    
    rect() {}
    rect(float x, float y, float w, float h) : w(h), h(h), vec4(x, y, w, h) {}

    operator SDL_Rect () const {
        return {(int)x, (int)y, (int)w, (int)h};
    }
};