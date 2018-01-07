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
    String& st = _lines[_curline];
    st.append(c);
}

std::ostream& operator<<(std::ostream& o, const Document& d)
{
    return o;
}



