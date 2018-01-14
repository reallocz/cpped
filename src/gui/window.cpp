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
        std::cerr << "SDL window/renderer couldn't be created!" << std::endl;
        close();
    }
    else
    {
        initGl();
        _canvas = Canvas(width, height);
        _running = true;
        std::cout << "Window created succesfully" << std::endl;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    std::cout << "Window destroyed." << std::endl;
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
        std::cerr << "Failed to initialize glad!" << std::endl;
        close();
    }
}

void Window::update()
{
    // TODO
    SDL_GL_SwapWindow(_window);
}

// Clear the screen and update the window size
void Window::clear()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    int width, height;
    SDL_GetWindowSize(_window, &width, &height); // SDL uses int and not uint
    _canvas.setWidth(width);
    _canvas.setHeight(height);
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

