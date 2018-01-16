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
    clearBuffer();
}


void Bitmap::clearBuffer()
{
    if(_buffer != nullptr)
    {
        delete[] _buffer;
        _buffer = nullptr;
    }
    else
        std::cerr << "Error:Bitmap: Calling dtor on nullptr!" << std::endl;
}


// Copy another buffer to our own
// Note needs
void Bitmap::copyBuffer(unsigned char* src)
{
    // Dont allocate memory for 0 size bitmaps
    unsigned long bufCount = _rows * _width;
    if(bufCount == 0)
    {
        //std::cerr << "Warn: Bitmap: Glyph has 0 width or 0 rows!"
            //<< std::endl;
        return;
    }

    if(_buffer != nullptr)
    {
        std::cout << "Warn:Bitmap: Overwriting an existing buffer"
            << std::endl;
        clearBuffer();
    }

    //_buffer = (unsigned char*) malloc(bufCount);
    _buffer = new unsigned char[bufCount];
    if(!_buffer)
    {
        std::cerr << "Error: copyBuffer - malloc failed!" << std::endl;
    }
    else
    {
        memcpy(_buffer, src, bufCount);
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
        for(unsigned int row = 0; row < _rows; ++row)
        {
            for(unsigned int c = 0; c < _width; ++c)
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

