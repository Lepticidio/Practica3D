#versión 430
layout (location = 0) in vec3 vertexPosition;
uniform mat4 shadowMVP;

void main(void)
{
	gl_Position = shadowMVP * vec4(vertexPos, 1.0);
}