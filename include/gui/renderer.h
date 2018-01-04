#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#define RDEFAULT_SIZE 120
#define RDEFAULT_PATH "fonts/DejaVuSans.ttf"

class Renderer {
public:
    Renderer(SDL_Renderer* renderer, unsigned int width, unsigned int height);
    virtual ~Renderer();
    void render(const char* string);
    void setFont(const char* path, unsigned int size);
    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

private:
    SDL_Renderer* _renderer;
    unsigned int _width, _height;
    TTF_Font* _font;
    unsigned int _size;
    std::string _path;
    SDL_Color _color;
};

