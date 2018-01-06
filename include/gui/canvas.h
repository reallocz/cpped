#pragma once
#include <SDL2/SDL.h>

struct Canvas
{
    Canvas(SDL_Renderer* renderer, unsigned int width, unsigned int height);
    virtual ~Canvas();

    SDL_Renderer* r;
    unsigned int w, h;
};
