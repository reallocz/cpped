#include "gui/renderer.h"

Renderer::Renderer() 
{
}


Renderer::~Renderer()
{
}


// Draws the document to canvas
void Renderer::renderdoc(Canvas& canvas, Document& d)
{
    unsigned int numlines = d.numlines();
    renderLine(canvas, d[0]);

#if 0
    for(unsigned int i = 0; i < numlines; ++i)
    {
        const Line& line = d[i];
        if(!line.isempty())
        {
            renderLine(canvas, line);
        }
    }
#endif

}


void Renderer::renderLine(Canvas& canvas, const Line& line)
{
    Bitmap b = _font.getBitmap('a');
}

