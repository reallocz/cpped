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


void Line::setNum(unsigned int num)
{
    _num = num;
}


String Line::slice(unsigned int from, unsigned int len) const
{
    return _str.slice(from, len);
}

void Line::setactive(bool value)
{
    _isactive = value;
}


bool Line::isactive() const
{
    return _isactive;
}


bool Line::isempty() const
{
    return _str.length() == 0;
}


unsigned int Line::number() const
{
    return _num;
}


unsigned int Line::length() const
{
    return _str.length();
}

void Line::print() const
{
    std::cout << "Line[" << _num << "] - ";
    _str.print();
}


const char* Line::data() const
{
    return _str.data();
}

