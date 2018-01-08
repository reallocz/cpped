#include "core/input.h"
#include <iostream>


Input::Input(Window& window, KEYCB cb):
    _window(window), keyCb(cb)
{}

Input::~Input() {}

void Input::poll()
{
    SDL_Event event;
    unsigned int type;

    while(SDL_PollEvent(&event))
    {
        type = event.type;

        if(type == SDL_KEYDOWN)   // Skip KEYUP
        {
            onKey(event.key);
        }
        else if(type == SDL_MOUSEMOTION)
        {
            onMouseMotion(event.motion);
        }
        else if(type == SDL_MOUSEBUTTONUP|| type == SDL_MOUSEBUTTONDOWN)
        {
            onMouseButton(event.button);
        }
        else if(type == SDL_MOUSEWHEEL)
        {
            onMouseWheel(event.wheel);
        }
        else if(type == SDL_QUIT)
        {
            onClose();
        }
    }

}


void Input::onKey(SDL_KeyboardEvent &event)
{
    //int code = event.keysym.scancode;
    int sym = event.keysym.sym;
    int mod = event.keysym.mod;

    //std::cout << mod << " , " << code << ", " << sym << "-> " << codeToChar(sym, mod) << std::endl;

    Keytype type;
    char c;

    type = getType(sym, mod);

    if(type == Keytype::Insert)
    {
        c = codeToChar(sym, mod);
    }

    Key k{type, c};

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

void Input::onClose()
{
    std::cout << "Close requested" << std::endl;
    _window.close();
}

char Input::codeToChar(int code, int mod)
{
    // alpha
    if(code >= 65 && code < 123)
    {
        if(mod == 1)
            return (char) (code - 32);  //Caps
        else
            return (char) code;
    }
    // TODO move numeric to catchall?
    // Numeric  
    else if(code >= 48 && code < 58)
    {
        return (char) code;  // 0-9
    }
    // catch all
    else if(code >= 32 && code < 127)
    {
        return (char) code;
    }
    else 
    {
        return '*'; // This shouldnt happen
    }
}

// asciitable.com
Keytype Input::getType(int code, int mod)
{
    if(code >= 32 && code < 127)
    {
        return Keytype::Insert;
    }

    // Backspace    delete          enter
    else if(code == 8 || code == 127 || code == 13)
    {
        return Keytype::Edit;
    }
    else
    {
        return Keytype::Nop;
    }
}
