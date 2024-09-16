#pragma once
#include <pch.h>
#include "fonts/fonts.hpp"

class drawing{
public:
    drawing(SDL_Renderer* pRenderer, SDL_Window* pWindow){
        this->pRenderer = pRenderer;
        this->pWindow = pWindow;
        this->pFont = new fonts();
    }

    rect* render_string(vec2 pos, std::string data, color4 color, int psize = 12){
        font_texture* tex = this->pFont->generate_string(this->pRenderer, data, psize, nullptr, color);
        SDL_Rect rect = *tex->set_pos(pos);
        SDL_RenderCopy(this->pRenderer, tex->tData, NULL, &rect);
        return &tex->tRect;
    }

    rect* render_fostring(vec2 pos, std::string data, color4 color, int psize = 12){
        render_string({pos.x-1, pos.y}, data, {0, 0, 0}, psize);
        render_string({pos.x, pos.y+1}, data, {0, 0, 0}, psize);
        render_string({pos.x, pos.y-1}, data, {0, 0, 0}, psize);
        render_string({pos.x+1, pos.y}, data, {0, 0, 0}, psize);

        return render_string(pos, data, color, psize);
    }

    rect* render_ostring(vec2 pos, std::string data, color4 color, int psize = 12){
        render_string({pos.x-1, pos.y}, data, {0, 0, 0}, psize);
        render_string({pos.x, pos.y+1}, data, {0, 0, 0}, psize);
        render_string({pos.x, pos.y-1}, data, {0, 0, 0}, psize);
        render_string({pos.x+1, pos.y}, data, {0, 0, 0}, psize);

        render_string({pos.x-1, pos.y-1}, data, {0, 0, 0}, psize);
        render_string({pos.x-1, pos.y+1}, data, {0, 0, 0}, psize);
        render_string({pos.x+1, pos.y-1}, data, {0, 0, 0}, psize);
        render_string({pos.x+1, pos.y+1}, data, {0, 0, 0}, psize);

        return render_string(pos, data, color, psize);
    }

    void render_line(vec2 start, vec2 end){
        SDL_RenderDrawLine(pRenderer, start.x, start.y, end.x, end.y);
    }

    void set_draw_color(color4 color){
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

    void implode(){
        this->pFont->implode();
        delete this;
    }

private:
    SDL_Renderer* pRenderer;
    SDL_Window* pWindow;
    fonts* pFont;
};