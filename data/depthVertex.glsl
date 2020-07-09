#version 430

uniform mat4 mvMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

attribute vec3 vpos;

void main()
{
	gl_Position = projectionMatrix * mvMatrix * vec4(vpos, 1);
}
