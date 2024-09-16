#pragma once
#include <pch.h>

class camera : public gameobject {
public:
    camera(rect* pWinSize, drawing* pDrawing) : pWinSize(pWinSize), pDrawing(pDrawing) {}
    
    vec2 w2s(vec3 pos, float scale = 1.0f);
    void render(std::unordered_map<std::string, gameobject*> &objs);
private:
    float fov = 90.f;
    rect* pWinSize;
    drawing* pDrawing;
};