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
varying vec3 fambient;
varying vec3 fdiffuse;
varying vec3 fcolor;

out vec3 varyingNormal;
out vec3 varyingLightDirs[99]; 
out vec3 varyingVertPos;
out vec3 varyingHalfVectors[99];
flat out int iNumberLightsOut;

struct Light
{ 
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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
	iNumberLightsOut = inumberlights;
	fambient = globalAmbient;

	vec4 P = mvMatrix * vec4(vpos,1.0);
	vec3 N = normalize((normalMatrix * vec4(vnormal,1.0)).xyz);
	vec3 Eye = normalize(-P.xyz);
	vec3 diffuse;
	for(int i = 0; i < inumberlights; i++)
	{

		
		vec3 L = normalize(lights[i].position - P.xyz);
		vec3 R = reflect(-L,N);

		//vec3 H = normalize((varyingLightDirs[i] + (-varyingVertPos)).xyz);
		//vec3 specular =  material.specular.xyz * light.specular.xyz * pow(max(cosAlpha, 0.0f), material.shininess);
	
		vec3 vWhite = vec3(1,1,1);
		diffuse.xyz += vWhite * material.diffuse.xyz *max(dot(N,L), 0.0);
	}

	fcolor = globalAmbient + diffuse;
	gl_Position = projectionMatrix * mvMatrix * vec4(vpos, 1);
	ftex = vtex;
	fambient = globalAmbient;
}
