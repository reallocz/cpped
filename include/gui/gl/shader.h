#pragma once
#include "config.h"
#include "glad/glad.h"
#include "log.h"
#include <map>

#define SDEF_VERTPATH CONF_RES_ROOT "shaders/vert.s"
#define SDEF_FRAGPATH CONF_RES_ROOT "shaders/frag.s"

class Shader
{
public:
    Shader();
    ~Shader();
    void use();

    void mapUniform(const char* name);

    // TODO Add setters
    void setUniform(const char* name, int val);

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

    // uniform name->location
    std::map<const char*, unsigned int> _unimap;
};

