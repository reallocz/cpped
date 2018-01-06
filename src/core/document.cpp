#include "core/document.h"
#include <iostream>

Document::Document()
{
    _filename = "";
    _lines = std::vector<std::string>();
    _curline = 0;
    _curcol = 0;
    _lines.push_back("");
}

Document::~Document()
{
    std::cout << "Document closed" << std::endl;
}

void Document::insert(char c)
{
    std::string& str = _lines[_curline];
    str.insert(_curcol, 1, c);
    moveRight();
    print();
}

void Document::moveRight()
{
    ++_curcol;
    std::cout << *this;
}

void Document::moveLeft()
{
    if(_curcol > 0)
        --_curcol;
    std::cout << this;
}

void Document::print() const
{
    for(auto line: _lines)
    {
        std::cout << line << std::endl;
    }
}



std::ostream& operator<<(std::ostream& o, const Document& d)
{
    o << "Cursor<" << d._curline << ", " << d._curcol << ">" << std::endl;
    return o;
}



