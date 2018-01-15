#include "gui/canvas.h"
#include "glad/glad.h"

Canvas::Canvas() {}


Canvas::Canvas(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    _isSizeChanged = false;
    updateViewport();
}


Canvas::~Canvas()
{
}


void Canvas::setSize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    updateViewport();
}


void Canvas::updateViewport()
{
    glViewport(0, 0, _width, _height);
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

