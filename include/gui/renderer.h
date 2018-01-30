#pragma once
#include "gui/canvas.h"
#include "gui/font.h"
#include "core/document.h"
#include "gui/gl/shader.h"
#include "gui/gl/vao.h"
#include "gui/gl/texture.h"
#include "log.h"




class Renderer 
{
public:
    Renderer();
    virtual ~Renderer();
    
    void renderdoc(Canvas& canvas, Document& d);

private:
    void renderLine(Canvas& canvas, const Line& line);
    void calcVerts(Glyph& glyph, Canvas& canvas, int row, int col, float* verts);

private:
    Font _font;
    Shader _shader;
    Vao _vao;
    Texture _atlasTex{0};
    // TODO Add dpi
    Log _log{"Renderer"};
};

