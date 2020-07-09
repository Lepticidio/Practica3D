#version 430

uniform sampler2D texSampler;
layout (binding=0) uniform sampler2D shText;
varying vec2 ftex;
varying vec3 fambient;
varying vec3 fdiffuse;
varying vec3 fcolor;

in vec4 shadow_coord;

void main()
{
    float closestDepth = texture2D(shText, shadow_coord.xy).r; 

    float currentDepth = shadow_coord.z;

	vec4 textureColor = texture2D( texSampler, ftex);

    vec4 vFragColor =  textureColor  * vec4(fcolor, 1.0f); 
    if( currentDepth > closestDepth)
    {
        vFragColor = vec4(fambient, 1.0f);
    }

	gl_FragColor = vFragColor;
    //gl_FragColor = vec4(vec3(currentDepth), 1.0f);

}
