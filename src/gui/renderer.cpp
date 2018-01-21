#include "gui/renderer.h"


Renderer::Renderer() 
{
    renderchar();
}


Renderer::~Renderer()
{
}



// TODO TEMPORARY!
void Renderer::renderchar()
{
    const Glyph& glyph = _font.getGlyph('3');

    std::cout << "Rendering: " << glyph.code << " -> " <<
        glyph.bmap_atlasoffset << std::endl;
    std::cout << "W, H" << "=" << glyph.bmap_width << ", "
        << glyph.bmap_rows << std::endl;

    glyph.print(_font.atlasbuffer());

    glGenTextures(1, &_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* What is this???? */

    const unsigned char* offset = &_font.atlasbuffer()[glyph.bmap_atlasoffset];

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
            glyph.bmap_width, glyph.bmap_rows,
            0, GL_RED, GL_UNSIGNED_BYTE,
            offset);

    glGenerateMipmap(GL_TEXTURE_2D);

    _shader.use();
    _vao.bind();

    _log << Log::L << "Renderer Initialized" << std::endl;
}


// Draws the document to canvas
void Renderer::renderdoc(Canvas& canvas, Document& d)
{
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
    //std::cout << "len: " << line.length() << std::endl;;
    const String& str = line.getString();
    int penX = 0;
    int linewidth = 0;

    // Main calc
    for(unsigned int i = 0; i < line.length(); ++i) {
        // Build a texture
        char ch = str[i];
        const Glyph& glyph = _font.getGlyph(ch);
        penX += glyph.advX >> 6; // 1/64th


        linewidth += glyph.width;
    }

    _shader.setUniform("xoff", 1);
    // TODO build line bitmap

    //std::cout << "Lw: " << linewidth << std::endl;
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


