#include "gui/canvas.h"


Canvas::Canvas(SDL_Renderer* renderer, unsigned int width, unsigned int height)
{
    r = renderer;
    w = width;
    h = height;
}

Canvas::~Canvas()
{
}

