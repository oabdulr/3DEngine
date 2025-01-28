#pragma once
#include <pch.h>

class engine
{
public:
    bool isRunning = true;
    
    engine(rect win_size) : win_size(win_size) {};

    bool quit();
    bool init();
    bool should_limit();
    int mesure_fps(bool end);
    int mesure_ticks(bool end);

    camera* create_camera();
    camera* get_pCamera();

    gameobject* create_object(std::string tag, gameobject* object);

    void set_title(std::string title);
    void events();
    void camera_render();
    void register_eventcall(gameobject* object);
    void event_call();
    void lock_mouse(bool lock);

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    drawing* pDrawing;

    float fps = 0.f;
private:
    const float FPS_LIMIT = 144.f;
    
    Uint32 fps_start_time, fps_frame_time = 0;
    Uint32 tic_start_time, tic_frame_time, delta = 0;
    rect win_size;

    camera* pCamera;
    std::unordered_map<std::string, gameobject*> objects {};
    std::queue<std::pair<int, SDL_Event>> event_queue {};
};