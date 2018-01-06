#pragma once
#include <SDL2/SDL.h>
#include "core/input.h"
#include "gui/canvas.h"

class Window {
public:
    Window(unsigned int width, unsigned int height, const char* title, Input input);
    virtual ~Window();

    void update();
    void clear();
    void poll();
    void close();
    inline bool running() const { return _running; };
    Canvas getCanvas() const;

private:
    unsigned int _width, _height;
    const char* _title;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    bool _running;
    Input _input;
};
