#version 430

in vec3 varyingNormal;
in vec3 varyingLightDirs[99];
in vec3 varyingHalfVectors[99];
in vec3 varyingVertPos;
flat in int iNumberLightsOut;

uniform sampler2D texSampler;
varying vec2 ftex;
varying vec3 fambient;
varying vec3 prediffuses[99];

void main()
{
	vec3 N = normalize(varyingNormal);
	vec3 Eye = normalize(-varyingVertPos);

	vec4 diffuse;
	diffuse.w = 1;

	for(int i = 0; i < iNumberLightsOut; i++)
	{
		//vec3 L  = normalize(fambient);
		//vec3 L = normalize(varyingLightDirs[i]);
		//vec3 H = normalize(varyingHalfVectors[i]);
		//vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(cosAlpha, 0.0f), material.shininess);
	
	
		//diffuse.xyz += prediffuses[i]*max(dot(N,L), 0.0);
	
	}
	

	diffuse.xyz = vec3(1, 1, 1);

	vec4 textureColor = texture2D( texSampler, ftex);


	gl_FragColor = textureColor  * (diffuse + vec4(fambient.x, fambient.y, fambient.z, 1.0f));
}
