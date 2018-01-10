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
