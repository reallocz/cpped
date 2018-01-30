#pragma once

class Texture
{
public:
    Texture(unsigned int unit);
    ~Texture();

    void bind();
    void setImage2D(unsigned int width, unsigned int height,
        unsigned char* data);
    unsigned int id();
    unsigned int unit();
    void print();

private:
    unsigned int _id;
    unsigned int _unit;
};
