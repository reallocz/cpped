#pragma once
#include <SDL2/SDL.h>
#include <functional>

struct Key
{
    char c;
};

using KEYCB = std::function<void(Key)>;

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

    char codeToChar(int code, int mod);

private:
    KEYCB keyCb;
};

