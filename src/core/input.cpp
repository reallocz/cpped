#include "core/input.h"
#include <iostream>

Input::Input(KEYCB cb):
    keyCb(cb)
{}

Input::~Input() {}


void Input::onKey(SDL_KeyboardEvent &event)
{
    keyCb(SDL_GetScancodeName(event.keysym.scancode));
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

