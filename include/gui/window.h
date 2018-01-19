#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "gui/canvas.h"
#include "log.h"

#define WDEF_WIDTH 400
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
    Canvas& getCanvas();
    void setTitle(const char* title);

private:
    void initGl();

private:
    const char* _title;
    bool _running;

    SDL_Window* _window;
    SDL_GLContext _glcontext;
    Canvas _canvas;

    Log _log{"Window"};
};
