#version 430 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D texture_diff;

void main()
{
	color = texture(texture_diff, TexCoord);
}