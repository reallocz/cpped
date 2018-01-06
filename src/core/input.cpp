#include "core/input.h"
#include <iostream>

Input::Input() {}

Input::Input(KEYCB cb):
    keyCb(cb)
{}

Input::~Input() {}


void Input::onKey(SDL_KeyboardEvent &event)
{
    //int code = event.keysym.scancode;
    int sym = event.keysym.sym;
    int mod = event.keysym.mod;

    //std::cout << mod << " , " << code << ", " << sym << "-> " << codeToChar(sym, mod) << std::endl;
    
    char c = codeToChar(sym, mod);
    Key k{c};
    keyCb(k);
}

void Input::onMouseMotion(SDL_MouseMotionEvent &event)
{
}

void Input::onMouseButton(SDL_MouseButtonEvent &event)
{
}

void Input::onMouseWheel(SDL_MouseWheelEvent &event)
{
}

char Input::codeToChar(int code, int mod)
{
    // Letters
    if(code >= 65 && code < 123)
    {
        if(mod == 1)
            return (char) (code - 32);  //Caps
        else
            return (char) code;
    }
    else if(code >= 48 && code < 58)
    {
        return (char) code;  // 0-9
    }
    return 'X';
}
