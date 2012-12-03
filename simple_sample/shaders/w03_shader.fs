#version 330

in vec4 vVaryingColor;
in vec2 vVaryingTexCoord0;

out vec4 vFragColor;

void main() 
{
	vFragColor = vVaryingColor;
}