#include <pch.h>
#include "engine/engine.h"

int main(int argc, char** argv) {
    engine* pEngine = new engine();
    if (int init = pEngine->init())
        return init;

    drawing* pDrawing = new drawing(pEngine->pRenderer, pEngine->pWindow);
    
    while (pEngine->isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) {
                case SDL_QUIT:
                    pEngine->isRunning = false;
                    break;
                default:
                    break;
            }
        }

        pDrawing->set_draw_color(0, 100, 100, 100);
        pDrawing->render_clear();
        pDrawing->set_draw_color(0, 0, 0, 255);
        pDrawing->render_preset();
    }

    return pEngine->quit_all();
}