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

String::String(const char* str)
    :String()
{
    unsigned int len = strlen(str);
    while(_size < len)
        doubleSize();
    strcpy(_data, str); 
}

String::~String() 
{
    delete[] _data;
}


void String::print() const
{
    std::cout << _data << "\n" << std::endl;
}


void String::append(char c)
{
    if(_len >= _size)
        doubleSize();

    std::cout << c << "-"  << _len << "/" << _size-1 << std::endl;
    _data[_len] = c;
    ++_len;
    print();
}


void String::doubleSize()
{
    std::cout << "\nDoubling " << _size << " -> " << _size * 2 << std::endl;

    _size *= 2;
    char* newdata = new char[_size];
    memset(newdata, 0, getSizeBytes());

    memcpy(newdata, _data, getLengthBytes());

    delete[] _data;
    _data = newdata;
}


unsigned int String::getSizeBytes() const
{
    return _size * sizeof(char);
}


unsigned int String::getLengthBytes() const
{
    return _len * sizeof(char);
}


char String::operator[](unsigned int pos) const
{
    if(pos > _len)
    {
        std::cerr <<  "String out of bound access" << std::endl;
        throw;
    }
    else
        return _data[pos];
}

void String::operator=(const char* str)
{
    unsigned int len = strlen(str);
    while(_size < len)
        doubleSize();
    strcpy(_data, str); 
}
