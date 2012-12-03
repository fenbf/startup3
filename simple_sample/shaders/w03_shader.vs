#version 330

uniform mat4x4 matModelview;
uniform mat4x4 matProjection;

layout(location=0) in vec4 vVertex;
layout(location=1) in vec4 vColor;
layout(location=3) in vec2 vTexCoord0;

out vec4 vVaryingColor;
out vec2 vVaryingTexCoord0;

void main() 
{
    vVaryingColor = vColor;
    vVaryingTexCoord0 = vTexCoord0;
    gl_Position = matProjection * matModelview * vVertex;
}