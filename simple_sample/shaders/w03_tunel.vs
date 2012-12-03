#version 330

uniform mat4x4 matModelview;
uniform mat4x4 matProjection;

// todo: declare animParam as uniform...

layout(location=0) in vec4 vVertex;
layout(location=1) in vec4 vColor;
layout(location=3) in vec2 vTexCoord0;

out vec4 vVaryingColor;
out vec2 vVaryingTexCoord0;
out vec2 vVaryingTexCoord1;

void main() 
{
    vVaryingColor = vColor;
    // todo: do something to animate texture movement...
    vVaryingTexCoord0 = vTexCoord0;
    vVaryingTexCoord1 = vTexCoord0;
    
    vec4 v = vVertex;
    // todo: do something to animate v.x and v.y    
    
    vec4 vOut = matProjection * matModelview * v;
    
    // todo: do something with the vVaryingColor to fade it out...
    
    gl_Position = vOut;
}