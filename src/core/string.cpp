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
    replace(str);
}


// copy ctor
String::String(const String& str)
    :String()
{
    replace(str.data());
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
    if(_len >= _size)
        doubleSize();

    std::cout << c << "-"  << _len << "/" << _size-1 << std::endl;
    _data[_len] = c;
    ++_len;
    print();
}


// Replace the current contents with the new one
void String::replace(const char* str)
{
    unsigned int len = strlen(str);
    while(_size < len)
        doubleSize();
    strcpy(_data, str);
    _len = len;
}


void String::doubleSize()
{
    std::cout << "\nDoubling " << _size << " -> " << _size * 2 << std::endl;
    _size *= 2;
    resize();
}


// Reduce size if possible
// NOTE: The length doesn't change!
void String::optimize()
{
    int safezone = 4;

    if(_size > (_len + safezone))
    {
        int oldsize = _size;

        std::cout << "len=" << _len << ", size=" << _size << std::endl;
        std::cout << "Optimizing: " << oldsize;

        _size = _len + safezone;
        // Keep _size even
        if((_size % 2) != 0)
            --_size;
        std::cout << " -> " << _size << ". (" << oldsize - _size << ") bytes" << std::endl;
        resize();
    }
}

// Copy old data to newdata. Called after changing _size.
void String::resize()
{
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
    replace(str);
}


const char* String::data() const
{
    return _data;
}


// Create and return a new string
String String::slice(unsigned int from, unsigned int len)
{
    if(len > (_len - from) || from > _len)
    {
        std::cout << "Invalid slice requested: [" << from << ", " << len
            << "] on string of length: " << _len << std::endl;;
        throw;
    }
    char* data = new char[len + 1];
    memcpy(data, &_data[from], len * sizeof(char));
    data[len] = '\0';
    return String(data);
}

