#pragma once
#include <SDL2/SDL.h>
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
    Font font;
    SDL_Color _color;
    // TODO Add dpi
};

