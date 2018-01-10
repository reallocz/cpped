#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Canvas
{
public:
    Canvas();
    Canvas(SDL_Renderer* renderer, unsigned int width, unsigned int height);
    virtual ~Canvas();

    const unsigned int width() const;
    const unsigned int height() const;

    void print() const;
    bool isDirty() const;

private:
    SDL_Renderer* _renderer;
    unsigned int _width, _height;
    bool _isSizeChanged;
};
