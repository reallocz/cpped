#include "gui/renderer.h"

Renderer::Renderer() 
{
    _size = RDEFAULT_SIZE;
    _path = RDEFAULT_PATH;

    setFont(_path.c_str(), _size);
    setColor(0, 0, 0, 255);
}


Renderer::~Renderer()
{
}

void Renderer::setFont(const char* path, unsigned int size)
{
}


void Renderer::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    std::cout << "Setting color<" << r << ", " << g << ", " << b << ", " << a << ">" << std::endl; 
    _color = {r, g, b, a};
}


// Draws the document to canvas
void Renderer::renderdoc(Canvas& canvas, Document& d)
{
    unsigned int numlines = d.numlines();
    for(unsigned int i = 0; i < numlines; ++i)
    {
        const Line& line = d[i];
        if(!line.isempty())
        {
            renderLine(canvas, line);
        }
    }

}


void Renderer::renderLine(Canvas& canvas, const Line& line)
{
}


void Renderer::calcSize(const char* str, int& width, int& height) const
{
}

