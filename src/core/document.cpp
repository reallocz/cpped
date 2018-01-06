#include "core/document.h"
#include <iostream>

Document::Document()
{
    _filename = "";
    _curline = 0;
}

Document::~Document()
{
    std::cout << "Document closed" << std::endl;
}

void Document::insert(char c)
{
    Line& line = _lines[_curline];
    line.insert(c);
    line.print();
}

std::ostream& operator<<(std::ostream& o, const Document& d)
{
    return o;
}



