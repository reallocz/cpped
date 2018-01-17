#pragma once


#define VDEF_VAL 99

class Vao
{
public:
    Vao();
    ~Vao();
    void bind();
    void unbind();

private:
    void checkVal(unsigned int val, const char* name);
private:
    unsigned int _vao, _vbo, _ebo; 
};
