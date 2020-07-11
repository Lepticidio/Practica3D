#version 430

layout (binding=1) uniform sampler2D texSampler;
layout (binding=0) uniform sampler2D shText;
varying vec2 ftex;
varying vec3 fambient;
varying vec3 fdiffuse;
varying vec3 fcolor;

in vec4 shadow_coord;

void main()
{

    vec4 shadowColor = vec4(1, 1, 1, 1);
    if ( texture2D(shText, shadow_coord.xy).r < shadow_coord.z- 0.0009 )
    {
        shadowColor = vec4(fambient, 1);
    }



	vec4 textureColor = texture2D( texSampler, ftex);

    vec4 vFragColor = shadowColor* textureColor  * vec4(fcolor, 1.0f); 


	//gl_FragColor = vec4(shadow_coord.z);
    //gl_FragColor = vec4(texture2D(shText, shadow_coord.xy).r);
    gl_FragColor = vFragColor;
}
