#include "gui/canvas.h"

Canvas::Canvas() {}

Canvas::Canvas(SDL_Renderer* renderer, unsigned int width, unsigned int height)
{
    _renderer = renderer;
    _width = width;
    _height = height;
    _isSizeChanged = false;
}

Canvas::~Canvas()
{
}


SDL_Renderer* Canvas::renderer()
{
    return _renderer;
}


void Canvas::setWidth(unsigned int width)
{
    _width = width;
}


void Canvas::setHeight(unsigned int height)
{
    _height = height;
}


void Canvas::setRenderer(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

const unsigned int Canvas::width() const
{
    return _width;
}


const unsigned int Canvas::height() const
{
    return _height;
}


bool Canvas::isDirty() const
{
    return _isSizeChanged;
}

void Canvas::print() const
{
    std::cout << "Canvas <w-" << width() << ", h-" << height() << ">" << std::endl;
}

