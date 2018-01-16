#include "gui/bitmap.h"
#include <iostream>
#include <cstring>


Bitmap::Bitmap()
{
    _rows = 0;
    _width = 0;
    _pitch = 0;
    _buffer = nullptr;
}

Bitmap::Bitmap(unsigned int rows, unsigned int width,
        int pitch, unsigned char* buffer)
    :Bitmap()
{
    // Note: Change operator= too, if you change this!
    _rows = rows;
    _width = width;
    _pitch = pitch;
    copyBuffer(buffer);
}


// Copy constructor
Bitmap::Bitmap(const Bitmap& b):
    Bitmap(b.rows(), b.width(), b.pitch(), b.buffer())
{
}


Bitmap& Bitmap::operator=(const Bitmap& b)
{
    _rows = b.rows();
    _width = b.width();
    _pitch = b.pitch();
    copyBuffer(b.buffer());
    return *this;
}


Bitmap::~Bitmap()
{
    if(_buffer != nullptr)
    {
        //std::cout << "DELETING BITMAP: " << &_buffer << std::endl;
        delete _buffer;
    }
    else
    {
        std::cout << "Calling dtor on nullptr!" << std::endl;
    }
}


// Copy another buffer to our own
// Note needs
void Bitmap::copyBuffer(unsigned char* src)
{
    if(_buffer != nullptr)
    {
        std::cout << "Warn: Overwriting an existing buffer"
            << std::endl;
        delete _buffer;
        _buffer = nullptr;
    }

    unsigned long bufSize = sizeof(unsigned char) * _rows * _width;
    _buffer = (unsigned char*) malloc(bufSize);
    if(!_buffer)
    {
        std::cerr << "Error: copyBuffer - malloc failed!" << std::endl;
    }
    else
    {
        memcpy(_buffer, src, bufSize);
    }
}


void Bitmap::print() const
{
    if(_buffer == nullptr)
    {
        std::cout << "ERROR: printing empty bitmap!" << std::endl;
    }
    else
    {
        for(int row = 0; row < _rows; ++row)
        {
            for(int c = 0; c < _width; ++c)
            {
                char x = _buffer[row * _width + c] == 0 ? ' ' : '.';
                std::cout << x;
            }
            std::cout << std::endl;
        }
    }

}



unsigned int Bitmap::rows() const
{
    return _rows;
}


unsigned int Bitmap::width() const
{
    return _width;
}

int Bitmap::pitch() const
{
    return _pitch;
}

unsigned char* Bitmap::buffer() const
{
    return _buffer;
}

