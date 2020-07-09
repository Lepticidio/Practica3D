#version 430

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

attribute vec3 vpos;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vpos, 1);
}
