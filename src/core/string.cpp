#include "core/string.h"
#include <iostream>
#include <memory.h>

String::String()
{
    _len = 0;
    _size = SDEF_SIZE;

    _data = new char[_size];
    memset(_data, 0, getSizeBytes());
}

String::~String() 
{
    delete[] _data;
}

void String::print() const
{
    std::cout << _data <<  "; " << std::endl;
}

void String::append(char c)
{
    std::cout << "\n" << c << "-"  << _len << "/" << _size << std::endl;
    if(_len >= _size)
        doubleSize();

    _data[_len] = c;
    ++_len;
}

void String::doubleSize()
{
    std::cout << "Doubling " << _size << " -> " << _size * 2 << std::endl;

    _size *= 2;
    char* newdata = new char[_size];
    memset(newdata, 0, getSizeBytes());
    memcpy(newdata, _data, getSizeBytes() / 2);

    delete[] _data;
    _data = newdata;
}

unsigned int String::getSizeBytes() const
{
    return _size * sizeof(char);
}
