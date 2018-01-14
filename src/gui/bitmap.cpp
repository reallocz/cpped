#include "gui/bitmap.h"
#include <iostream>

Bitmap::Bitmap()
{
    _rows = 0;
    _width = 0;
    _pitch = 0;
    _buffer = nullptr;
}


Bitmap::Bitmap(unsigned int rows, unsigned int width, int pitch, unsigned char* buffer)
{
    _rows = rows;
    _width = width;
    _pitch = pitch;
    _buffer = buffer;
}


Bitmap::Bitmap(const Bitmap& b)
    :Bitmap(b.rows(), b.width(), b.pitch(), b.buffer())
{
}


Bitmap::~Bitmap()
{
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

void Bitmap::print()
{
    if(_buffer == nullptr) std::cout << "ERROR" << std::endl;

    for(int row = 0; row < rows(); ++row)
    {
        for(int c = 0; c < width(); ++c)
        {
            if(c % 3 == 0) std::cout << ' ';
            std::cout << (int) _buffer[row * width() + c] << '.';
        }
        std::cout << std::endl;
    }
}

