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
	vec4 P = mvMatrix * vec4(vpos, 1);
	vec3 N = normalize((normalMatrix * vec4(vnormal, 1)).xyz);
	//vec3 ambient = ((globalAmbient* material.ambient) + (light.ambient*material.ambient)).xyz;
	//vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz*max(dot(N,L), 0.0);
	//vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(R, Eye), 0.0f), material.shininess);
	vec3 ambient = globalAmbient;
	vec3 diffuse;
	
	for(int i = 0; i < inumberlights; i++)
	{
		Light light = lights[i];

		vec3 L = normalize(light.position - P.xyz);
		vec3 Eye = normalize(-P.xyz);
		vec3 R = reflect(-L, N);

		diffuse += light.diffuse.xyz * material.diffuse.xyz*max(dot(N,L), 0.0);
	}
	
	gl_Position = projectionMatrix * mvMatrix * vec4(vpos, 1);
	ftex = vtex;
	fcolor = vcolor;
}
