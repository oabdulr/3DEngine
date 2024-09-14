#pragma once
#include <pch.h>

class font{
public:
    font() {}
    font(std::unordered_map<int, TTF_Font*> fData, std::string fName, std::string fPath, int fSize) : fData(fData), fName(fName), fPath(fPath), fSize(fSize) {}
    font(std::string fName, std::string fPath, int fSize = 12) : fName(fName), fPath(fPath), fSize(fSize) 
    {
        this->fData.emplace(fSize, TTF_OpenFont(fPath.c_str(), fSize));
    }

    TTF_Font* sdl_font(int psize) { return this->resize(psize); }
    TTF_Font* sdl_font() { return this->fData[default_size]; }
    bool is_valid() { return this->fData[default_size]; };
    void implode() { delete this; }

private:
    const char* default_font = "arial.ttf";
    const int default_size = 12;

    std::string fName;
    std::string fPath;
    int fSize;

    TTF_Font* resize(int psize){
        if (fData.find(psize) == fData.end())
            this->fData.emplace(psize, TTF_OpenFont(fPath.c_str(), psize));
        return fData[psize];
    }

    std::unordered_map<int, TTF_Font*> fData {};
};