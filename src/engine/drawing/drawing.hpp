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

    void render_line(vec3 start, vec3 end){
        SDL_RenderDrawLine(pRenderer, start.x, start.y, end.x, end.y);
    }

    void render_dline(vec3 start, vec3 end){
        SDL_RenderDrawLine(pRenderer, start.x - 1, start.y, end.x - 1, end.y);
        SDL_RenderDrawLine(pRenderer, start.x + 1, start.y, end.x + 1, end.y);
        SDL_RenderDrawLine(pRenderer, start.x, start.y - 1, end.x, end.y - 1);
        SDL_RenderDrawLine(pRenderer, start.x, start.y + 1, end.x, end.y + 1);
        SDL_RenderDrawLine(pRenderer, start.x, start.y, end.x, end.y);
    }


    void render_pixel(vec2 start){
        SDL_RenderDrawPointF(pRenderer, start.x, start.y);
    }

    void render_pixel(vec2 start, color4 col){
        set_draw_color(col);
        SDL_RenderDrawPointF(pRenderer, start.x, start.y);
    }

    void render_quat(rect r) {
        SDL_Rect sdl_r = r;
        
        SDL_RenderFillRect(pRenderer, &sdl_r);
    }

    void render_geomerty(const vec3 vertices[3]){
        SDL_Vertex s_verts[3];
        s_verts[0].position = { vertices[0].x, vertices[0].y };
        s_verts[0].color = rdraw_color;
        s_verts[1].position = { vertices[1].x, vertices[1].y };
        s_verts[1].color = rdraw_color;
        s_verts[2].position = { vertices[2].x, vertices[2].y };
        s_verts[2].color = rdraw_color;
        SDL_RenderGeometry(pRenderer, nullptr, s_verts, 3, nullptr, 0);
    }

    void set_draw_color(color4 color){
        rdraw_color = color;
        SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.alpha);
    }
    void set_draw_color(int r, int g, int b, int alpha = 255){
        rdraw_color = {(float)r, (float)g, (float)b, (float)alpha};
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
    color4 rdraw_color = {0, 0, 0, 0};

    SDL_Renderer* pRenderer;
    SDL_Window* pWindow;
    fonts* pFont;
};