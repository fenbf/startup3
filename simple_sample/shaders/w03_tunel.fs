#version 330

in vec4 vVaryingColor;
in vec2 vVaryingTexCoord0;
in vec2 vVaryingTexCoord1;

out vec4 vFragColor;

// todo: declare texture units...

void main() 
{
	// todo: read from textures...
	vFragColor = vVaryingColor;
}