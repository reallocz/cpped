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


std::ostream& operator<<(std::ostream& o, const Canvas& c)
{
    o << "Canvas<" << c.w << ", " << c.h << ">" << std::endl;
    return o;
}
