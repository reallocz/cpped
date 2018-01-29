#pragma once
#include "gui/canvas.h"
#include "gui/font.h"
#include "core/document.h"
#include "gui/gl/shader.h"
#include "gui/gl/vao.h"
#include "log.h"




class Renderer 
{
public:
    Renderer();
    virtual ~Renderer();
    
    void renderdoc(Canvas& canvas, Document& d);

private:
    void renderLine(Canvas& canvas, const Line& line);
    void calcVerts(Glyph& glyph, int row, int col, float* verts);

private:
    Font _font;
    Shader _shader;
    Vao _vao;
    unsigned int _tex;
    // TODO Add dpi
    Log _log{"Renderer"};
};

