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

    this->pWindow = SDL_CreateWindow("SLD test", this->win_size.x, this->win_size.y, this->win_size.w, this->win_size.h, 0);
    if (!this->pWindow) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_SOFTWARE);
    if (!this->pRenderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pDrawing = new drawing(this->pRenderer, this->pWindow);
    this->create_camera();

    return EXIT_SUCCESS;
}

bool engine::should_limit(){
    return  (frame_time > 0) ? this->frame_time > 1000.f / this->FPS_LIMIT : false;
}

int engine::mesure_fps(bool end){
    if (!end){
        this->start_time = SDL_GetTicks();
        return 0;
    }

    this->frame_time = SDL_GetTicks()-start_time;
    this->fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
    return this->fps;
}

camera* engine::create_camera(){
    return this->pCamera = new camera(&this->win_size, this->pDrawing);
}

camera* engine::get_pCamera(){
   return this->pCamera;
}

gameobject* engine::create_object(std::string tag, gameobject* object){
    if (this->objects.find(tag) != this->objects.end())
        return nullptr;
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
            default:
                break;
        }
    }
}

void engine::camera_render(){
    this->pCamera->render(this->objects);
}