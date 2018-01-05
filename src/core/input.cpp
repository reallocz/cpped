#include "core/input.h"
#include <iostream>

Input::Input() {}

Input::~Input() {}


void Input::onKey(SDL_KeyboardEvent &event)
{
    std::cout << event.keysym.scancode << std::endl;
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

