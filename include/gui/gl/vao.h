#pragma once
#include "log.h"
#include <vector>

#define VDEF_VAL 99

class Vao
{
public:
    Vao();
    ~Vao();
    void bind();
    void unbind();
    void bufferVertices(long size, float* verts);
    void bufferIndices(long size, int* verts);

private:
    void checkVal(unsigned int val, const char* name);
private:
    unsigned int _vao, _vbo, _ebo; 
    Log _log{"Vao"};
    bool _isbound;
};
