#pragma once
#include <pch.h>

class drawing{
public:
    drawing(SDL_Renderer* pRenderer, SDL_Window* pWindow){
        this->pRenderer = pRenderer;
        this->pWindow = pWindow;
    }

     void get_text_and_rect(
            SDL_Renderer* renderer, int x, int y, char* text,
            TTF_Font* font, SDL_Texture** texture, SDL_Rect* rect) {

        int text_width;
        int text_height;
        SDL_Surface* surface;
        SDL_Color textColor = { 255, 255, 255, 0 };

        surface = TTF_RenderText_Solid(font, text, textColor);
        *texture = SDL_CreateTextureFromSurface(renderer, surface);
        text_width = surface->w;
        text_height = surface->h;
        SDL_FreeSurface(surface);
        rect->x = x;
        rect->y = y;
        rect->w = text_width;
        rect->h = text_height;
    }


    void set_draw_color(color4 &color){
        SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.alpha);
    }
    void set_draw_color(int r, int g, int b, int alpha){
        SDL_SetRenderDrawColor(pRenderer, r, g, b, alpha);
    }
    
    void render_clear(){
        SDL_RenderClear(pRenderer);
    }
    void render_preset(){
        SDL_RenderPresent(pRenderer);
    }
private:
    SDL_Renderer* pRenderer;
    SDL_Window* pWindow;
};