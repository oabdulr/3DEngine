#pragma once
#include <pch.h>

class font_texture{
public:
    font_texture(font* font, std::string data, color4 color, int psize, SDL_Renderer* pRenderer) 
    {
        int text_width;
        int text_height;
        SDL_Surface* surface;

        surface = TTF_RenderText_Blended(font->sdl_font(psize), data.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
        text_width = surface->w;
        text_height = surface->h;
        SDL_FreeSurface(surface);
        tRect.w = text_width;
        tRect.h = text_height;

        this->tData = texture;
    }

    rect* set_pos(vec2 pos){
        this->tRect.x = pos.x;
        this->tRect.y = pos.y;
        return &tRect;
    }

    void implode(){
        SDL_DestroyTexture(this->tData);
        delete this;
    }

    SDL_Texture* tData;
    rect tRect;
private:
};