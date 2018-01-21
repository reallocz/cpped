#include "gui/gl/vao.h"
#include "glad/glad.h"
#include <iostream>

static
const float vertices[] = {
    0, 0, 0, 0, 1,
    1, 0, 0, 1, 1,
    1, 1, 0, 1, 0,
    0, 1, 0, 0, 0,
};

static
const int indices[] = {
    0, 1, 2,
    0, 3, 2
};

Vao::Vao():
    _vao(VDEF_VAL), _vbo(VDEF_VAL), _ebo(VDEF_VAL)
{
    glGenVertexArrays(1, &_vao);
    checkVal(_vao, "_vao");
    glBindVertexArray(_vao);

    // Vbo
    glGenBuffers(1, &_vbo);
    checkVal(_vbo, "_vbo");
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
            GL_STATIC_DRAW);

    // Ebo
    glGenBuffers(1, &_ebo);
    checkVal(_ebo, "_ebo");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
            GL_STATIC_DRAW);

    ///  Attribs
    // quad verts
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
            (void*) 0);
    glEnableVertexAttribArray(0);
    // tex coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind!
    glBindVertexArray(0);
}


Vao::~Vao()
{
    unbind();
}


void Vao::bind()
{
    glBindVertexArray(_vao);
}


void Vao::unbind()
{
    glBindVertexArray(0);
}


void Vao::checkVal(unsigned int val, const char* name)
{
    if(val == VDEF_VAL)
    {
        std::cerr << "Error: Vao: Failed to init : " << name
            << std::endl;
    }
}
