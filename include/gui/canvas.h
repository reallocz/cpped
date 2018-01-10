#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Canvas
{
    friend class Window;

public:
    Canvas();
    Canvas(SDL_Renderer* renderer, unsigned int width, unsigned int height);
    virtual ~Canvas();

    SDL_Renderer* renderer();
    const unsigned int width() const;
    const unsigned int height() const;

    void print() const;
    bool isDirty() const;

private:
    void setWidth(unsigned int width);
    void setHeight(unsigned int width);
    void setRenderer(SDL_Renderer* renderer);

private:
    SDL_Renderer* _renderer;
    unsigned int _width, _height;
    bool _isSizeChanged;
};
