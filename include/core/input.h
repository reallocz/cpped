#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include "gui/window.h"
#include "log.h"

enum class Keytype {
    Insert,     // Alphanumeric, spacebar
    Edit,       // Backspace, enter, delete
    Movement,   // Arrows and home/pgup etc
    Nop         // No operation
};

struct Key
{
    Keytype type;
    char c;
};

using KEYCB = std::function<void(Key)>;

class Input
{
public:
    Input(Window &window, KEYCB cb);
    virtual ~Input();
    void poll();

private:
    void onKey(SDL_KeyboardEvent &event);
    void onMouseMotion(SDL_MouseMotionEvent &event);
    void onMouseButton(SDL_MouseButtonEvent &event);
    void onMouseWheel(SDL_MouseWheelEvent &event);
    void onClose();

    char codeToChar(int code, int mod);
    Keytype getType(int code, int mod);

private:
    Window &_window;
    KEYCB keyCb;
    Log _log{"Input"};
};

