#version 460 core

out vec4 FragColor;

in vec2 TexCoord; 

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

void main()
{
    vec4 diffuseColor = texture(texture_diffuse1, TexCoord);
    vec4 specularColor = texture(texture_specular1, TexCoord);
    vec4 normalMap = texture(texture_normal1, TexCoord);

    FragColor = diffuseColor * 0.8 + specularColor * 0.2;  // Ajuste os fatores conforme necessário
}
