#version 430

uniform int inumberlights;

uniform vec3 globalAmbient;
uniform mat4 mvMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

attribute vec3 vpos;
attribute vec3 vnormal;
attribute vec2 vtex;
attribute vec3 vcolor;

varying vec2 ftex;
varying vec3 fcolor;

out vec3 varyingNormal;
out vec3 varyingLightDirs[99]; 
out vec3 varyingVertPos;
out int iNumberLightsOut;

struct Light
{ 
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};


uniform Light lights[99];


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
	varyingNormal = (normalMatrix * vec4(vnormal,1.0)).xyz;
	varyingVertPos = (mvMatrix * vec4(vpos,1.0)).xyz;
	iNumberLightsOut = inumberlights;
	for(int i = 0; i < inumberlights; i++)
	{
		varyingLightDirs[i] = lights[i].position - varyingVertPos;
	}
	//

	gl_Position = projectionMatrix * mvMatrix * vec4(vpos, 1);
	ftex = vtex;
	fcolor = vcolor;
}
