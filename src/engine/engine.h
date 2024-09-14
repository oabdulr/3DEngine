#pragma once
#include <pch.h>


#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

class engine
{
public:
    bool isRunning = true;
    
    bool quit();
    bool init();

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
private:
};