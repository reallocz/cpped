#include "gui/window.h"
#include <iostream>
#include <SDL2/SDL.h>

Window::Window(): Window(400, 400, "New File") {}

Window::Window(unsigned int width, unsigned int height,
        const char* title):
    _width(width), _height(height), _title(title) 
{
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow(_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_RESIZABLE);
    if(_window == NULL)
    {
        std::cerr << "SDL window couldn't be created!" << std::endl;
        close();
    }
    else
    {
        _renderer = SDL_CreateRenderer(_window, -1, 0);
        if(_renderer == NULL)
        {
            std::cerr << "Failed to create renderer!" << std::endl;
            close();
        }
        else
        {
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            _running = true;
            _input = Input();
            std::cout << "Window created successfully!" << std::endl;
        }
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

void Window::clear()
{
    SDL_RenderClear(_renderer);
}

void Window::poll()
{
    SDL_Event event;
    unsigned int type;

    while(SDL_PollEvent(&event)) 
    {
        type = event.type;

        if(type == SDL_KEYDOWN || type == SDL_KEYUP)
        {
            _input.onKey(event.key);
        }
        else if(type == SDL_MOUSEMOTION)
        {
            _input.onMouseMotion(event.motion);
        }
        else if(type == SDL_MOUSEBUTTONUP|| type == SDL_MOUSEBUTTONDOWN)
        {
            _input.onMouseButton(event.button);
        }
        else if(type == SDL_MOUSEWHEEL)
        {
            _input.onMouseWheel(event.wheel);
        }
        else if(type == SDL_QUIT)
        {
            close();
        }

    }
}

void Window::close()
{
    _running = false;
}
