#pragma once
#include <SDL2/SDL.h>
#include <functional>


using KEYCB = std::function<void(const char*)>;

class Input
{
public:
    Input();
    Input(KEYCB cb);
    virtual ~Input();

    void onKey(SDL_KeyboardEvent &event);
    void onMouseMotion(SDL_MouseMotionEvent &event);
    void onMouseButton(SDL_MouseButtonEvent &event);
    void onMouseWheel(SDL_MouseWheelEvent &event);


private:
    KEYCB keyCb;
};
