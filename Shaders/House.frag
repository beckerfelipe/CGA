#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    vec3 diffuseTex = texture(texture_diffuse1, TexCoords).rgb;
    vec3 specularTex = texture(texture_specular1, TexCoords).rgb;
    //FragColor = vec4(1.0,0.0,0.0, 1.0);
    FragColor = vec4(diffuseTex, 1.0);
}