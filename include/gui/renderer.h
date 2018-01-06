#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "gui/canvas.h"
#include "core/document.h"

#define RDEFAULT_SIZE 120
#define RDEFAULT_PATH "fonts/DejaVuSans.ttf"

class Renderer 
{
public:
    Renderer();
    virtual ~Renderer();
    void setFont(const char* path, unsigned int size);
    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    

    void render(Canvas canvas, Document& d);

private:
    TTF_Font* _font;
    unsigned int _size;
    std::string _path;
    SDL_Color _color;
    // TODO Add dpi
};

