#include "core/string.h"
#include <iostream>
#include <memory.h>

String::String()
{
    _len = 0;
    _size = LDEFAULT_SIZE;

    _data = new char[_size];
    memset(_data, 0, _size * sizeof(char));
}

String::~String() 
{
    delete[] _data;
}

void String::print() const
{
    std::cout << _data << std::endl;
}

void String::append(char c)
{
    if(_len < _size)
    {
        _data[_len] = c;
        ++_len;
    }
    else
    {
        doubleSize();
        append(c);
    }
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
