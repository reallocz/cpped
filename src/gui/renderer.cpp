#include "gui/renderer.h"

Renderer::Renderer(SDL_Renderer* renderer, unsigned int width, unsigned int height):
    _renderer(renderer), _width(width), _height(height),
    _size(RDEFAULT_SIZE), _path(RDEFAULT_PATH)
{
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


void Renderer::render(const char* string)
{
    SDL_Surface* surf = TTF_RenderText_Solid(_font, string, _color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(_renderer, surf);
    SDL_RenderCopy(_renderer, tex, NULL, NULL);
    SDL_FreeSurface(surf);
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
