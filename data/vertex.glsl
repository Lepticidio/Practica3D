#version 430

uniform vec3 ambient;
uniform mat4 mvMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

attribute vec3 vpos;
attribute vec3 vnormal;
attribute vec2 vtex;
attribute vec3 vcolor;

varying vec2 ftex;
varying vec3 fcolor;

struct PositionalLight
{ 
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
uniform PositionalLight light;

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};
uniform Material material;


void main()
{
	vec4 P = mvMatrix * vec4(vpos, 1);
	vec3 N = normalize((normalMatrix * vec4(vnormal, 1)).xyz);
	vec3 L = normalize(light.position - P.xyz);


	vec3 Eye = normalize(-P.xyz);
	vec3 R = reflect(-L, N);

	gl_Position = projectionMatrix * mvMatrix * vec4(vpos, 1);
	ftex = vtex;
	fcolor = vcolor;
}
