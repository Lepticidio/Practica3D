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
    float closestDepth = texture(shText, shadow_coord.xy).r; 

    float currentDepth = shadow_coord.z;

    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;



	vec4 textureColor = texture2D( texSampler, ftex);

    vec4 vFragColor = vec4(fambient, 1.0f);
    //vec4 vFragColor = textureColor  * vec4(fcolor, 1.0f); 
    if(shadow == 0)
    {
        vFragColor = textureColor  * vec4(fcolor, 1.0f); 
    }

	gl_FragColor = vFragColor;

}
