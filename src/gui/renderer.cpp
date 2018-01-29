#include "gui/renderer.h"


// TODO create a texture class.
// TODO add getTextureId in Shader.h
// TODO Calculate vwidth and vheight from canvas size and font size


Renderer::Renderer() 
{
    int numchars = _font.glyphcount();
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
}


Renderer::~Renderer()
{
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
    int numglyphs = str.length();

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
    int vertsperbuf = 4 * 4; // rows * cols
    int numverts = numglyphs * vertsperbuf;
    float* verts = new float[numverts];

    for(int i = 0; i < numglyphs; ++i)
    {
        Glyph glyph = _font.getGlyph(str[i]);
        calcVerts(glyph, canvas, 0, i, &verts[i*16]);
    }



    /// Rendering!!!
    _shader.use();
    _vao.bind();
    _vao.bufferIndices(sizeof(int) * numindices, &indices[0]);
    _vao.bufferVertices(sizeof(float) * numverts, &verts[0]);
    _shader.setUniform("xoff", 1);

    // the next two calls enable transparency and blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw calls
    glDrawElements(GL_TRIANGLES, 6 * numglyphs, GL_UNSIGNED_INT, 0);
}


/**
 * Calculate the verts for the glyph
 * variables prefixed with 'v' are vert related in range [0, 1]
 * variables prefixed with 't' are texture related in range [0, 1]
 */
void Renderer::calcVerts(Glyph& glyph, Canvas& canvas, int row, int col, float* verts)
{
    int numchars = _font.glyphcount();
    int gindex = glyph.atlas_index; // For calculating texcoords

    float fontsizepx = _font.sizepx();
    float vheight = fontsizepx / canvas.height();
    float vwidth = fontsizepx / canvas.width();

    //float vwidth = 0.08;
    //float vheight = 0.16;
    float vtopedge = 1 - (vheight * row);
    float vleftedge = 1.* col * vwidth - 1;

    float twidth = 1.0;
    float theight = 1.0/numchars;
    float ttopedge = gindex * 1./numchars;
    float tleftedge = 0.;

    // YOLOSDLKF
    // Topleft
    verts[0] = vleftedge;
    verts[1] = vtopedge;
    verts[2] = tleftedge;
    verts[3] = ttopedge;

    // topright
    verts[4] = vleftedge + vwidth;
    verts[5] = vtopedge;
    verts[6] = tleftedge + twidth;
    verts[7] = ttopedge;

    // bottom left
    verts[8] = vleftedge;
    verts[9] = vtopedge - vheight;
    verts[10] = tleftedge;
    verts[11] = ttopedge + theight;

    // bottom right 
    verts[12] = vleftedge + vwidth;
    verts[13] = vtopedge - vheight;
    verts[14] = tleftedge + twidth;
    verts[15] = ttopedge + theight;

    //// Debug info
    //std::cout << "Vertices: \n";
    //for(int j = 0; j < 4; ++j)
    //{
        //std::cout
            //<< "\t" << verts[j*4 +0] << ", "
            //<< "\t" << verts[j*4 +1] << ", "
            //<< "\t" << verts[j*4 +2] << ", "
            //<< "\t" << verts[j*4 +3] << ", "
            //<< std::endl;
    //}
}






/* Notes:
 *
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

// Previous Verts calc
/*
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
        glyph.printInfo();
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
*/


