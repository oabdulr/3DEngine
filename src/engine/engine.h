#pragma once
#include <pch.h>

class engine
{
public:
    bool isRunning = true;
    
    engine(rect win_size) : win_size(win_size) {};

    bool quit();
    bool init();
    int mesure_fps(bool end);

    camera* create_camera();
    camera* get_pCamera();

    gameobject* create_object(std::string tag, gameobject* object);

    void set_title(std::string title);
    void events();
    void camera_render();

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    drawing* pDrawing;
private:
    Uint32 start_time, frame_time;
    float fps = 0.f;
    rect win_size;

    camera* pCamera;
    std::unordered_map<std::string, gameobject*> objects {};
};