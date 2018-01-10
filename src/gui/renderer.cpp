#include "gui/renderer.h"

Renderer::Renderer() 
{
    _size = RDEFAULT_SIZE;
    _path = RDEFAULT_PATH;

    if(TTF_Init() == -1)
        std::cout << "TTFInit: " << TTF_GetError() << std::endl;
    setFont(_path.c_str(), _size);
    setColor(0, 0, 0, 255);
}


Renderer::~Renderer()
{
    TTF_CloseFont(_font);
    TTF_Quit();
}

void Renderer::setFont(const char* path, unsigned int size)
{
    _size = size;
    _path = path;
    _font = TTF_OpenFont(_path.c_str(), _size);    
    if(_font == NULL)
        std::cerr << "Failed to set TTFFont: " << TTF_GetError() << std::endl;
    else
        std::cout << "Changed font to: " << _path << std::endl;
}


void Renderer::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    std::cout << "Setting color<" << r << ", " << g << ", " << b << ", " << a << ">" << std::endl; 
    _color = {r, g, b, a};
}


// Draws the document to canvas
void Renderer::renderdoc(Canvas& canvas, Document& d)
{
    unsigned int numlines = d.numlines();
    for(unsigned int i = 0; i < numlines; ++i)
    {
        const Line& line = d[i];
        if(!line.isempty())
        {
            renderLine(canvas, line);
        }
    }

}


void Renderer::renderLine(Canvas& canvas, const Line& line)
{
    int lwidth = (int) calcWidth(line.data());
    int cwidth = lwidth / line.length();


    //std::cout << "Rendering: ";
    //line.print();
    //std::cout << "Width: " << lwidth << std::endl;

    SDL_Surface* surf = NULL;

    if(lwidth >= (int) canvas.width())
    {
        int numvisible = canvas.width() / cwidth;
        std::cout << line.slice(0, numvisible - 5).data() << std::endl;
        surf = TTF_RenderText_Solid(_font, line.slice(0, numvisible - 5).data(), _color);
        // TODO update lwdith here
    }
    else
    {
        surf = TTF_RenderText_Solid(_font, line.data(), _color);
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(canvas.renderer(), surf);

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0 + (line.number() * _size);
    dst.w = lwidth;
    dst.h = _size;

    SDL_RenderCopy(canvas.renderer(), tex, NULL, &dst);
    SDL_FreeSurface(surf);

}


unsigned int Renderer::calcWidth(const char* str) const
{
    int width;
    TTF_SizeText(_font, str, &width, NULL);
    return width;
}

