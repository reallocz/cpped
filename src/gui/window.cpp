#include "gui/window.h"
#include <iostream>
#include <SDL2/SDL.h>

Window::Window():
    Window(WDEF_WIDTH, WDEF_HEIGHT, WDEF_TITLE)
{
}

Window::Window(unsigned int width, unsigned int height,
        const char* title)
{
    _width = width;
    _height = height;
    _title = title;
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow(_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_RESIZABLE);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    _canvas = Canvas(_renderer, _width, _height);

    if(_window != NULL && _renderer != NULL)
    {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        _running = true;
    }
    else
    {
        std::cerr << "SDL window/renderer couldn't be created!" << std::endl;
        close();
    }
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    std::cout << "Window destroyed!?" << std::endl;
    SDL_Quit();
}

void Window::update()
{
    SDL_RenderPresent(_renderer);
}

// Clear the screen and update the window size
void Window::clear()
{
    SDL_RenderClear(_renderer);
    SDL_GetWindowSize(_window, (int*)&_width, (int*)&_height); // SDL uses int and not uint
}


void Window::close()
{
    _running = false;
}


const Canvas& Window::getCanvas() const
{
    return _canvas;
}

void Window::setTitle(const char* title)
{
    _title = title;
    SDL_SetWindowTitle(_window, _title);
}

