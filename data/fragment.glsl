#version 430

layout (binding=0) uniform sampler2D shText;
layout (binding=1) uniform sampler2D texSampler;
varying vec2 ftex;
varying vec3 fambient;
varying vec3 fdiffuse;
varying vec3 fcolor;

in vec4 shadow_coord;

void main()
{
    vec3 projCoords = shadow_coord.xyz / shadow_coord.w;

    float closestDepth = texture2D(shText, projCoords.xy).r; 

    float currentDepth = projCoords.z;

	vec4 textureColor = texture2D( texSampler, ftex);

    vec4 vFragColor =  textureColor  * vec4(fcolor, 1.0f); 
    if( currentDepth > closestDepth)
    {
        vFragColor = vec4(fambient, 1.0f);
    }

	gl_FragColor = vFragColor;
   //gl_FragColor = vec4(vec3(closestDepth), 1.0f);

}
