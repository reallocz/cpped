#pragma once
#include "config.h"
#include "glad/glad.h"
#include "log.h"

#define SDEF_VERTPATH CONF_RES_ROOT "shaders/vert.s"
#define SDEF_FRAGPATH CONF_RES_ROOT "shaders/frag.s"

class Shader
{
public:
    Shader();
    ~Shader();
    void use();

    // TODO Add setters

private:
    int create(GLuint type);
    void checkShaderStatus(unsigned int id, const char* name);
    void checkProgramStatus();
    void compile(int id, const char* path);

private:
    unsigned int _id;
    const char* _vertPath;
    const char* _fragPath;
    Log _log{"Shader"};
};

