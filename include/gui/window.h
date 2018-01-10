#pragma once
#include <SDL2/SDL.h>
#include "gui/canvas.h"

#define WDEF_WIDTH 300
#define WDEF_HEIGHT 600
#define WDEF_TITLE "New File"

class Window {
public:
    Window();
    Window(unsigned int width, unsigned int height, const char* title);
    virtual ~Window();

    void update();
    void clear();
    void close();
    inline bool running() const { return _running; };
    const Canvas& getCanvas() const;
    void setTitle(const char* title);

private:
    unsigned int _width, _height;
    const char* _title;
    bool _running;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    Canvas _canvas;
};
