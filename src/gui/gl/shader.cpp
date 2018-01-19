#include "gui/gl/shader.h"
#include "core/string.h"
#include <iostream>

Shader::Shader()
{
    _vertPath = SDEF_VERTPATH;
    _fragPath = SDEF_FRAGPATH;

    int vid, fid;
    vid = create(GL_VERTEX_SHADER);
    fid = create(GL_FRAGMENT_SHADER);
    compile(vid, _vertPath);
    compile(fid, _fragPath);

    // Link program
    _id = glCreateProgram();
    glAttachShader(_id, vid);
    glAttachShader(_id, fid);
    glLinkProgram(_id);
    checkProgramStatus();
    glDeleteShader(vid);
    glDeleteShader(fid);
}


Shader::~Shader()
{
}


void Shader::use()
{
    glUseProgram(_id);
}


// Create a new shader
int Shader::create(GLuint type)
{
    int id;
    id = glCreateShader(type);
    if(id == 0)
        _log << Log::E << __func__ << ":Failed to create shader!" << std::endl;
    return id;
}


void Shader::compile(int id, const char* path)
{
    String s = String::fromFile(path);
    if(!s.empty())
    {
        const char* data = s.data();
        glShaderSource(id, 1, &data, NULL);
        glCompileShader(id);
        checkShaderStatus(id, path);
    }
    else
    {
        _log << Log::E << __func__ << ": compilation failed - " << path << std::endl;
    }
}


void Shader::checkShaderStatus(unsigned int id, const char* name)
{
    char infolog[512];
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infolog);
        _log << Log::E << __func__  <<":compilation failed: " << infolog
            << std::endl;
    }
    else
    {
        _log << Log::L << __func__ << ": " << name << " compiled successfully"
            << std::endl;
    }
}


void Shader::checkProgramStatus()
{
    char infolog[512];
    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(_id, 512, NULL, infolog);
        _log << Log::E << __func__ << "Program creation failed: "
            << infolog << std::endl;
    }
    else
    {
        _log << Log::L << __func__ << ":Program compiled successfully!"
            << std::endl;
    }
}

