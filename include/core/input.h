#pragma once
#include <SDL2/SDL.h>


class Input
{
public:
    Input();
    virtual ~Input();
    void onKey(SDL_KeyboardEvent &event);
    void onMouseMotion(SDL_MouseMotionEvent &event);
    void onMouseButton(SDL_MouseButtonEvent &event);
    void onMouseWheel(SDL_MouseWheelEvent &event);
};
