#version 430



uniform sampler2D texSampler;
varying vec2 ftex;
varying vec3 fambient;
varying vec3 fdiffuse;

void main()
{



	vec4 textureColor = texture2D( texSampler, ftex);


	gl_FragColor = textureColor  * (vec4(fdiffuse.x, fdiffuse.y, fdiffuse.z, 1.0f) + vec4(fambient.x, fambient.y, fambient.z, 1.0f));
}
