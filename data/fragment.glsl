
uniform sampler2D texSampler;
varying vec2 ftex;
varying vec3 fcolor;
varying vec3 nvector;
varying vec3 fdiffuse;
varying vec3 fspecular;

struct Light 
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
};

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
}

uniform Light light;

uniform Material material;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{





	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// combine results
	vec3 ambient = light.ambient * material.ambientColor;
	vec3 diffuse = light.diffuse * diff * material.diffuseColor;
	vec3 specular = light.specular * spec * material.specularColor;

	return (ambient + diffuse + specular);
}


void main()
{
	vec3 lightDir = normalize(-light.direction);

	vec3 L = normalize(varyingLightDir);
	vec3 N = normalize(varyingNormal);
	vec3 Eye = normalize(-varyingVertPos);

	vec3 R = normalize(reflect(-L, N));

	float cosTheta = dot(L,N);
	float cosAlpha = dot(Eye,R);

	vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient *material.ambient)).xyz;

	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz* max(cosTheta, 0.0);

	vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(cosAlpha, 0.0f), material.shininess);
	fragColor = vec4((ambient + diffuse + specular), 1.0);

	textureColor = texture2D( texSampler, ftex)
	gl_FragColor = textureColor * ( ambientLight + diffuseLight + specularLight )

	gl_FragColor = texture2D( texSampler, ftex) * vec4(fcolor, 1);
}
