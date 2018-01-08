#include "core/document.h"
#include <iostream>

Document::Document()
{
    _filename = DDEF_FILENAME;
    _curline = 0;
}

Document::~Document()
{
    std::cout << "Document closed" << std::endl;
}

void Document::exec(Doccmd cmd)
{
    switch (cmd.type)
    {
    case Doccmd::Type::Insertchar:
        std::cout << "CMD: insertchar" << std::endl;
        break;
    case Doccmd::Type::Edit:
        std::cout << "CMD: eidt" << std::endl;
        break;
    case Doccmd::Type::Move:
        std::cout << "CMD: move" << std::endl;
        break;
    case Doccmd::Type::Save:
        std::cout << "CMD: Save" << std::endl;
        break;
    default:
        std::cout << "Default cmd" << std::endl;
        break;
    }
}

std::ostream& operator<<(std::ostream& o, const Document& d)
{
    return o;
}



