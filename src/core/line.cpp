#include "core/line.h"

Line::Line(unsigned int number):
    _num(number)
{
    _cur = 0;
}

Line::~Line()
{
}

// Insert character at curpos
void Line::insertChar(char a, unsigned int curpos)
{
}

// Delete char at curpos
void Line::deleteChar(unsigned int curpos)
{
}

