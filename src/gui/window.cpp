#include "gui/window.h"
#include <iostream>

Window::Window():
    Window(WDEF_WIDTH, WDEF_HEIGHT, WDEF_TITLE)
{
}

Window::Window(unsigned int width, unsigned int height,
        const char* title)
{
    _title = title;

    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow(_title, SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if(_window == NULL)
    {
        _log << Log::E << __func__ <<
            ":SDL window/renderer couldn't be created!" << std::endl;
        close();
    }
    else
    {
        initGl();
        _canvas = Canvas(width, height);
        _running = true;
        _log << Log::L << __func__ <<
            ":Window created succesfully" << std::endl;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    _log << Log::L << __func__ <<
        ":Window destroyed." << std::endl;
    SDL_Quit();
}


void Window::initGl()
{
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE );

    _glcontext = SDL_GL_CreateContext(_window);

    if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
    {
        _log << Log::E << __func__ <<
            ":Failed to initialize glad!" << std::endl;
        close();
    }
}

void Window::update()
{
    // TODO
    SDL_GL_SwapWindow(_window);

    int width, height;
    SDL_GetWindowSize(_window, &width, &height); // SDL uses int and not uint
    _canvas.setSize(width, height);
}


// Clear the screen
void Window::clear()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
}


void Window::close()
{
    _running = false;
}


Canvas& Window::getCanvas()
{
    return _canvas;
}


void Window::setTitle(const char* title)
{
    _title = title;
    SDL_SetWindowTitle(_window, _title);
}

