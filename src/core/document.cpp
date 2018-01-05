#include "core/document.h"
#include <iostream>

Document::Document()
{
    _filename = "";
    _lines = std::vector<std::string>();
    _curline = 0;
    _curcol = 0;
}


Document::~Document()
{
    std::cout << "Document closed" << std::endl;
}


void Document::insert(char c)
{
    _lines[_curline][_curcol] = c;
    moveRight();
}

void Document::moveRight()
{
    ++_curcol;
    log();
}

void Document::moveLeft()
{
    if(_curcol > 0)
        --_curcol;
    log();
}

void Document::print() const
{
    for(auto line: _lines)
    {
        std::cout << line << std::endl;
    }
}

void Document::log() const
{
    std::cout << "Cursor<" << _curline << ", " << _curcol << ">" << std::endl;
}
