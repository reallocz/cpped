#pragma once
#include "core/string.h"

class Line
{
public:
    Line();
    Line(unsigned int number);
    ~Line();

    void insertChar(char a);
    void deleteChar();

    void setactive(bool value);
    bool isactive();

private:
    String _str;
    unsigned int _num;
    bool _isactive;
};
