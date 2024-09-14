#include "engine.h"

bool engine::quit_all(){
    // todo, loop all textures and death
    //SDL_DestroyTexture(texture1);
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

    this->pWindow = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!this->pWindow) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_SOFTWARE);
    if (!this->pRenderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

   return EXIT_SUCCESS;
}