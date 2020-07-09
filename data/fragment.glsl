#version 430

uniform sampler2D texSampler;
varying vec2 ftex;
varying vec3 fambient;
varying vec3 fdiffuse;
varying vec3 fcolor;

void main()
{
	gl_FragColor =  vec4(vec3(1.0f, 1.0f, 0.0f), 1.0f);
}
