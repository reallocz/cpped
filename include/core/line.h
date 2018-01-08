#pragma once
#include "core/string.h"

class Line
{
public:
    Line(unsigned int number);
    ~Line();

    unsigned int curpos() const { return _cur; }
    void insertChar(char a, unsigned int curpos);
    void deleteChar(unsigned int curpos);

private:
    String _str;
    unsigned int _num;
    unsigned int _cur;
};
