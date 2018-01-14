#pragma once

class Bitmap
{
public:
    Bitmap();
    Bitmap(unsigned int rows, unsigned int width, int pitch, unsigned char* buffer);
    Bitmap(const Bitmap& b);
    ~Bitmap();

    unsigned int rows() const;
    unsigned int width() const;
    int pitch() const;
    unsigned char* buffer() const;

    void print();

private:
    unsigned int _rows, _width;
    int _pitch;
    unsigned char* _buffer;
};
