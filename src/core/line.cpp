#include "core/line.h"
#include <iostream>

Line::Line(): Line(0) {}

Line::Line(unsigned int number):
    _num(number)
{
    _isactive = false;
}

Line::~Line()
{
}

// Insert character at curpos
void Line::insertChar(char a)
{
    if(isactive())
        _str.append(a);
    else
        std::cout << "WARN: Inserting char on inactive line!" << std::endl;
}


// Delete char at curpos
void Line::deleteChar()
{
    if(isactive())
        return;
    else
        std::cout << "WARN: Deleting char on inactive line!" << std::endl;
}


void Line::setactive(bool value)
{
    _isactive = value;
}

bool Line::isactive()
{
    return _isactive;
}

