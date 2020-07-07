#version 430

layout (location = 0) in vec3 vertexPos;
uniform mat4 shadowMVP;

void main()
{
	gl_Position = shadowMVP * vec4(vertexPos, 1.0);
}