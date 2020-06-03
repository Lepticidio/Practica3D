#version 430



uniform sampler2D texSampler;
varying vec2 ftex;
varying vec3 fambient;
varying vec3 fdiffuse;
varying vec3 fcolor;

void main()
{



	vec4 textureColor = texture2D( texSampler, ftex);


	gl_FragColor = textureColor  * vec4(fcolor, 1.0f);
	//gl_FragColor = textureColor  * (vec4(1, fdiffuse.y, 1, 1.0f) + vec4(fambient.x, fambient.y, fambient.z, 1.0f));
}
