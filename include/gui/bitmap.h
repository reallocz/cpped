#pragma once
#include "log.h"

class Bitmap
{
public:
    Bitmap();
    Bitmap(unsigned int rows, unsigned int width, int pitch,
            unsigned char* buffer);

    // Copy
    Bitmap(const Bitmap& src);
    // Copy assigment
    Bitmap& operator=(const Bitmap& src);

    ~Bitmap() noexcept;

    void print() const;
    unsigned int rows() const;
    unsigned int width() const;
    int pitch() const;
    unsigned char* buffer() const;

private:
    void copyBuffer(unsigned char* src);
    void clearBuffer();

private:
    unsigned int _rows, _width;
    int _pitch;
    unsigned char* _buffer;
};
