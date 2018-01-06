#include "core/line.h"
#include <iostream>
#include <memory.h>

Line::Line()
{
    _len = 0;
    _cur = 0;
    _size = LDEFAULT_SIZE;

    _data = new char[_size];
    memset(_data, 0, _size * sizeof(char));
}

Line::~Line() 
{
    delete[] _data;
}

void Line::print() const
{
    std::cout << _data << std::endl;
}

void Line::insert(char c)
{
    // TODO UPDATE LOGIC!
    if(_cur < _size)
    {
        _data[_cur] = c;
        ++_cur;
        ++_len;
    }
    else
    {
        doubleSize();
        insert(c);
    }
}

void Line::doubleSize()
{
        std::cout << "Doubling " << _size << " -> " << _size * 2 << std::endl;
        _size *= 2;
        char* newdata = new char[_size];
        memset(newdata, 0, _size * sizeof(char));
        memcpy(newdata, _data, _len);
        delete[] _data;
        _data = newdata;
}
