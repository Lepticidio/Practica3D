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
	vec3 direction;
	float attenuation;
	int type;
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
	vec3 vWhite = vec3 (1,1,1);

	iNumberLightsOut = inumberlights;
	fambient = globalAmbient;

	vec4 P = mvMatrix * vec4(vpos,1.0);
	vec3 N = normalize((normalMatrix * vec4(vnormal,1.0)).xyz);
	vec3 Eye = normalize(-P.xyz);
	vec3 diffuse;
	vec3 specular;
	for(int i = 0; i < inumberlights; i++)
	{
		vec3 L = normalize(lights[i].position - P.xyz);

		if(lights[i].type == 0)
		{
			L = normalize(-lights[i].direction);
		}
		float NDotL = dot(N, L);

		float att = 1;
		

		if(lights[i].type == 0)
		{			
			diffuse.xyz += lights[i].diffuse.xyz * material.diffuse.xyz * max(NDotL, 0.0);
		}
		else
		{
			att = 1 / (1 + lights[i].attenuation * length(vpos-lights[i].position));
			diffuse.xyz += lights[i].diffuse.xyz*att * material.diffuse.xyz * max(NDotL, 0.0);
		}
		
		vec3 H = normalize(L - normalize(P.xyz));
		
		if(NDotL > 0)
		{
			float NdotH = dot(N, H);
			if(NdotH > 0)
			{
				specular +=  pow(NdotH, material.shininess) * att;
			}
		}




		

	}

	fcolor = globalAmbient + diffuse + specular;
	gl_Position = projectionMatrix * mvMatrix * vec4(vpos, 1);
	ftex = vtex;
	fambient = globalAmbient;
}
