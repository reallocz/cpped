#pragma once
#include <SDL2/SDL.h>
#include <iostream>

struct Canvas
{
    Canvas(SDL_Renderer* renderer, unsigned int width, unsigned int height);
    virtual ~Canvas();
    friend std::ostream& operator<<(std::ostream& o, const Canvas& c);

    SDL_Renderer* r;
    unsigned int w, h;
};
