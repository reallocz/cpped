#pragma once
#include "gui/canvas.h"
#include "gui/font.h"
#include "core/document.h"



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
    // TODO Add dpi
};

