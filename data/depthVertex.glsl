#version 430

layout (location = 0) 
attribute vec3 vpos;
uniform mat4 shadowMVP;

void main()
{
	gl_Position = shadowMVP * vec4(vpos, 1.0);
}