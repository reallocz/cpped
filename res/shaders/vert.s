#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aCoord;

out vec2 TexCoord;

uniform int xoff;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y - (xoff/64.0f), 0 , 1.0);
    TexCoord = aCoord;
}
