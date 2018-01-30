#include "gui/gl/texture.h"
#include "glad/glad.h"
#include <iostream>


Texture::Texture(unsigned int unit)
{
    _unit = unit;
    glGenTextures(1, &_id);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* IMPORTANT */
}


Texture::~Texture()
{
}


void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0 + _unit);
    glBindTexture(GL_TEXTURE_2D, _id);
}


unsigned int Texture::id()
{
    return _id;
}

unsigned int Texture::unit()
{
    return _unit;
}


void Texture::setImage2D(unsigned int width, unsigned int height,
        unsigned char* data)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
            width, height,
            0, GL_RED, GL_UNSIGNED_BYTE,
            data);
    glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture::print()
{
    std::cout << "Texture {"
        << "\nid: " << _id
        << "\nunit: " << _unit
        << "\n}" << std::endl;
}

