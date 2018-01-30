#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D fontAtlasTexture;

void main()
{
    FragColor = texture(fontAtlasTexture, TexCoord).rrrr * vec4(0, 0, 0, 1); // rrrr = white * green
} 
