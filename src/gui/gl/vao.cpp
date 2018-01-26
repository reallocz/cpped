#include "gui/gl/vao.h"
#include "glad/glad.h"
#include <iostream>


static
const int indices[] = {
    0, 1, 2,
    0, 2, 3
};

Vao::Vao():
    _vao(VDEF_VAL), _vbo(VDEF_VAL), _ebo(VDEF_VAL), _isbound(false)
{
    glGenVertexArrays(1, &_vao);
    checkVal(_vao, "_vao");
    glBindVertexArray(_vao);

    // Vbo
    glGenBuffers(1, &_vbo);
    checkVal(_vbo, "_vbo");
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Ebo
    glGenBuffers(1, &_ebo);
    checkVal(_ebo, "_ebo");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    ///  Attribs
    // quad verts
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
            (void*) 0);
    glEnableVertexAttribArray(0);
    // tex coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
            (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind!
    glBindVertexArray(0);
}


Vao::~Vao()
{}


void Vao::bind()
{
    if(_isbound)
    {
        std::cout << "VAO: Binding an already bound buffer!"
            << std::endl;
    }
    else
    {
        glBindVertexArray(_vao);
        _isbound = true;
    }
}


void Vao::unbind()
{
    if(_isbound)
        glBindVertexArray(0);
    else
        std::cerr << "VAO: Unbinding unbound buffer!" << std::endl;
}


// NOTE: Vao must be bound before buffering data!
void Vao::bufferVertices(long size, float* vertices)
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void Vao::bufferIndices(long size, int* indices)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}


void Vao::checkVal(unsigned int val, const char* name)
{
    if(val == VDEF_VAL)
    {
        std::cerr << "Error: Vao: Failed to init : " << name
            << std::endl;
    }
}
