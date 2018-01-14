#pragma once
#include <iostream>

class Canvas
{
    friend class Window;

public:
    Canvas();
    Canvas(unsigned int width, unsigned int height);
    virtual ~Canvas();

    const unsigned int width() const;
    const unsigned int height() const;

    void print() const;
    bool isDirty() const;

private:
    void setWidth(unsigned int width);
    void setHeight(unsigned int width);

private:
    unsigned int _width, _height;
    bool _isSizeChanged;
};
