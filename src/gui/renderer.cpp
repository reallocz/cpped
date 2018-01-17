#include "gui/renderer.h"


Renderer::Renderer() 
{
    std::cout << "init renderer!" << std::endl;
    const Bitmap& bm = _font.getGlyph('B').bitmap;
    glGenTextures(1, &_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //????
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bm.width(), bm.rows(), 0, GL_RED, GL_UNSIGNED_BYTE, bm.buffer());
    glGenerateMipmap(GL_TEXTURE_2D);

    _shader.use();
    _vao.bind();
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

