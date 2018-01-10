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
    bool isactive() const;
    bool isempty() const;
    unsigned int number() const;
    void print() const;
    const char* data() const;

private:
    String _str;
    unsigned int _num;
    bool _isactive;
};
