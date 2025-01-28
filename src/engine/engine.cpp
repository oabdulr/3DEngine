#include "engine.h"

bool engine::quit(){
    TTF_Quit();

    SDL_DestroyRenderer(this->pRenderer);
    SDL_DestroyWindow(this->pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}

bool engine::init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pWindow = SDL_CreateWindow("SLD test", this->win_size.x, this->win_size.y, this->win_size.w, this->win_size.h, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS);
    if (!this->pWindow) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_SOFTWARE);
    if (!this->pRenderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    this->lock_mouse(true);
    this->pDrawing = new drawing(this->pRenderer, this->pWindow);
    this->create_camera();

    return EXIT_SUCCESS;
}

void engine::lock_mouse(bool lock){
    SDL_SetWindowMouseGrab(this->pWindow, static_cast<SDL_bool>((int)lock));
}

bool engine::should_limit(){
    if (this->delta > 1000.f / this->FPS_LIMIT){
        this->delta = 0;
        return true;
    }

    return  false;
}

int engine::mesure_ticks(bool end){
    if (!end){
        this->tic_start_time = SDL_GetTicks();
        return 0;
    }

    this->tic_frame_time = SDL_GetTicks() - this->tic_start_time;
    this->delta += this->tic_frame_time;
    return this->tic_frame_time;
}

int engine::mesure_fps(bool end){
    if (!end){
        this->fps_start_time = SDL_GetTicks();
        return 0;
    }

    this->fps_frame_time = SDL_GetTicks() - this->fps_start_time;
    this->fps = (this->fps_frame_time > 0) ? 1000.0f / this->fps_frame_time : 0.0f;
    return this->fps;
}

camera* engine::create_camera(){
    this->pCamera = new camera(&this->win_size, this->pDrawing);
    this->create_object("camera", this->pCamera);
    return this->pCamera;
}

camera* engine::get_pCamera(){
   return this->pCamera;
}

gameobject* engine::create_object(std::string tag, gameobject* object){
    if (this->objects.find(tag) != this->objects.end())
        return nullptr;

    object->tag = tag;
    this->objects.emplace(tag, object);
    return this->objects[tag];
}

void engine::set_title(std::string title){
    SDL_SetWindowTitle(this->pWindow, title.c_str());
}

void engine::events(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) {
            case SDL_QUIT:
                this->isRunning = false;
                break;
            case SDL_MOUSEWHEEL:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYUP:
            case SDL_KEYDOWN:
            case SDL_MOUSEMOTION:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    this->lock_mouse(false);

                this->event_queue.push(std::pair(event.type, event));
            default:
                break;
        }
    }
}

void engine::camera_render(){
    this->pCamera->update();
    this->pCamera->render(this->objects);
}

void engine::event_call(){
    while (!this->event_queue.empty()) {
        for (auto& event_pair : this->objects)
            event_pair.second->event_input(this->event_queue.front().first, this->event_queue.front().second);
        
        this->event_queue.pop();
    }
}