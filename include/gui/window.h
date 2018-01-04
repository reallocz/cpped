#pragma once
#include <SDL2/SDL.h>

class Window {
public:
    Window();
    Window(unsigned int width, unsigned int height, const char* title);
    virtual ~Window();

    void update();
    void clear();
    void poll();
    void close();
    inline bool running() const { return _running; };
    inline SDL_Renderer* renderer() { return _renderer; };

private:
    unsigned int _width, _height;
    const char* _title;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    bool _running;
};
