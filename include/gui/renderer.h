#pragma once
#include "gui/canvas.h"
#include "gui/font.h"
#include "core/document.h"
#include "gui/shader.h"




class Renderer 
{
public:
    Renderer();
    virtual ~Renderer();
    
    void renderdoc(Canvas& canvas, Document& d);

private:
    void renderLine(Canvas& canvas, const Line& line);

private:
    Font _font;
    Shader s;
    unsigned int VAO, VBO, EBO;
    unsigned int tex;
    // TODO Add dpi
};

