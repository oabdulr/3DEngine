#pragma once
#include <pch.h>

class fonts{
public:
    fonts(){
        TTF_Init();
        this->create_font(this->default_path);
    }

    font* create_font(std::string path){
        std::string ttf_name = utility::split(path, '/').back();

        if (this->cached_fonts.find(ttf_name) != this->cached_fonts.end())
            return this->cached_fonts[ttf_name]; 
            
        font* pFont = new font(ttf_name, path);
        if (pFont->is_valid()){
            this->cached_fonts.emplace(ttf_name, pFont);
            return pFont;
        }

        pFont->implode();
        fprintf(stderr, "error: font not found\n");
        return nullptr;
    }

    font_texture* generate_string(SDL_Renderer* pRenderer, std::string data, int psize = 12, font* font = nullptr, color4 color = {255, 255, 255, 0}){
        if (!font)
            font = cached_fonts["arial.ttf"];
        std::string name_size = data + std::to_string(psize) + color.to_string();
        if (this->cached_textures.find(name_size) != this->cached_textures.end())
            return this->cached_textures[name_size];

        font_texture* tex = new font_texture(font, data, color, psize, pRenderer);
        cached_textures.emplace(name_size, tex);
        return tex;
    }

    void implode(){
        for (auto& pFont : cached_fonts){
            pFont.second->implode();
        }
        for (auto& pTex : cached_textures){
            pTex.second->implode();
        }
    }


private:
    const char* default_path = "../arial.ttf";

    std::unordered_map<std::string, font*> cached_fonts {};
    std::unordered_map<std::string, font_texture*> cached_textures {};
};