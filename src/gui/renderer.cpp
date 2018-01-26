#include "gui/renderer.h"
// TODO
// * Generate proper texcoords for each glyph!!!


Renderer::Renderer() 
{
    //renderchar();
    renderline();
}


Renderer::~Renderer()
{
}



// TODO TEMPORARY!
void Renderer::renderchar()
{
    const Glyph& glyph = _font.getGlyph('G');


    glGenTextures(1, &_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* What is this???? */

    unsigned char* offset = (unsigned char*)_font.atlasbuffer();
    //_font.printarb(offset);


    int numchars = _font.atlaswidth() / _font.atlascharwidth();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
            _font.atlascharwidth(), _font.atlascharheight()*numchars,
            0, GL_RED, GL_UNSIGNED_BYTE,
            offset);

    glGenerateMipmap(GL_TEXTURE_2D);

    int id = glyph.atlas_index;
    float vertices[] = {
        0, 1, 0,   id* 1./numchars,
        1, 1, 1,   id* 1./numchars,
        0, 0, 0,   id* 1./numchars + 1./numchars,
        1, 0, 1,   id* 1./numchars + 1./numchars,
    };

    int indices[] = {
        0, 1, 2,
        2, 3, 1
    };

    _shader.use();
    _vao.bind();

    _vao.bufferIndices(sizeof(int) * 6, &indices[0]);
    _vao.bufferVertices(sizeof(vertices), &vertices[0]);
    _log << Log::L << "Renderer Initialized" << std::endl;
}


/*
 * SRC(Bitmap buffer)
 *
 * (0,0)      (w, 0)
 *  *----------*
 *  |          |
 *  |          |
 *  *----------*
 * (0,h)      (w, h)
 *
 *
 *  DST(GL)
 * (0,1)      (1, 1)
 *  *----------*
 *  |          |
 *  |          |
 *  *----------*
 * (0,0)      (1, 0)
 *
 * verts : x, y, tx, ty * 4rows
 */

static
const int numglyphs = 6;
void Renderer::renderline()
{
    Glyph glyphs[] = {
        _font.getGlyph('e'),
        _font.getGlyph('d'),
        _font.getGlyph('i'),
        _font.getGlyph('t'),
        _font.getGlyph('o'),
        _font.getGlyph('r')};
    //Glyph glyphs[] = {_font.getGlyph('8')};

    // Init indices
    int numindices = numglyphs * 6;
    int* indices = new int[numindices];
    int vertrows = 4;
    for(int i = 0; i < numglyphs; ++i)
    {
        indices[i*6 + 0] = i*vertrows + 0;
        indices[i*6 + 1] = i*vertrows + 1;
        indices[i*6 + 2] = i*vertrows + 2;
        indices[i*6 + 3] = i*vertrows + 2;
        indices[i*6 + 4] = i*vertrows + 3;
        indices[i*6 + 5] = i*vertrows + 1;
    }


    // Init verts
    float vwidth = 0.1;
    float vheight = 0.5;
    int vertsperbuf = 4 * 4; // rows * cols
    int numverts = numglyphs * vertsperbuf;
    float* verts = new float[numverts];
    int numchars = _font.glyphcount();

    for(int i = 0; i < numglyphs; ++i)
    {
        Glyph glyph = glyphs[i];
        int gindex = glyph.atlas_index;

        float vleftedge = 1. * i * vwidth;
        float texleftedge = 0.;
        float textopedge = gindex * 1./numchars;
        float texwidth = 1.0;
        float texheight = 1.0/numchars;

        // Topleft
        verts[(i*vertsperbuf)+0] = vleftedge;
        verts[(i*vertsperbuf)+1] = vheight;
        verts[(i*vertsperbuf)+2] = texleftedge;
        verts[(i*vertsperbuf)+3] = textopedge;

        // topright
        verts[(i*vertsperbuf)+4] = vleftedge + vwidth;
        verts[(i*vertsperbuf)+5] = vheight;
        verts[(i*vertsperbuf)+6] = texleftedge + texwidth;
        verts[(i*vertsperbuf)+7] = textopedge;

        // bottom left
        verts[(i*vertsperbuf) + 8] = vleftedge;
        verts[(i*vertsperbuf) + 9] = 0;
        verts[(i*vertsperbuf) + 10] = texleftedge;
        verts[(i*vertsperbuf) + 11] = textopedge + texheight;

        // bottom right 
        verts[(i*vertsperbuf) + 12] = vleftedge + vwidth;
        verts[(i*vertsperbuf) + 13] = 0;
        verts[(i*vertsperbuf) + 14] = texleftedge + texwidth;
        verts[(i*vertsperbuf) + 15] = textopedge + texheight;
    }

    for(int i = 0; i < numglyphs; ++i)
    {
        std::cout << "Vertices: \n";
        for(int j = 0; j < 4; ++j)
        {
            std::cout
                << "\t" << verts[i*vertsperbuf + j*4 +0] << ", "
                << "\t" << verts[i*vertsperbuf + j*4 +1] << ", "
                << "\t" << verts[i*vertsperbuf + j*4 +2] << ", "
                << "\t" << verts[i*vertsperbuf + j*4 +3] << ", "
                << std::endl;
        }

        std::cout << "Indices \n"
            << indices[i*6+0] << ", "
            << indices[i*6+1] << ", "
            << indices[i*6+2] << ", \n"
            << indices[i*6+3] << ", "
            << indices[i*6+4] << ", "
            << indices[i*6+5] << ", \n"
            << std::endl;
    }

    // YOLO!!
    glGenTextures(1, &_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* What is this???? */

    unsigned char* texture = (unsigned char*)_font.atlasbuffer();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
            _font.atlascharwidth(),_font.atlascharheight()*numchars,
            0, GL_RED, GL_UNSIGNED_BYTE,
            texture);
    glGenerateMipmap(GL_TEXTURE_2D);

    _shader.use();
    _vao.bind();
    _vao.bufferIndices(sizeof(int) * numindices, &indices[0]);
    _vao.bufferVertices(sizeof(float) * numverts, &verts[0]);
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
    glDrawElements(GL_TRIANGLES, 6 * numglyphs, GL_UNSIGNED_INT, 0);
}


