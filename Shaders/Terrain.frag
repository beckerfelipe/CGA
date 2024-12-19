#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;    // Posição do fragmento no espaço do mundo
in vec3 Normal;     // Normal do fragmento no espaço do mundo

uniform sampler2D texture_diffuse1;    // Textura Diffuse
uniform sampler2D texture_specular1;   // Textura Specular
uniform sampler2D texture_normal1;     // Textura Normal
uniform vec3 lightPos;                 // Posição da luz no espaço do mundo
uniform vec3 cameraPos;                  // Posição da câmera no espaço do mundo
uniform vec3 lightColor = vec3(1.0,1.0,1.0);
uniform float currentTime;

void main()
{
    vec4 diffuseColor = texture(texture_diffuse1, TexCoord);
    vec4 specularColor = texture(texture_specular1, TexCoord);
    vec4 normalMap = texture(texture_normal1, TexCoord);

    vec3 normal = normalize(normalMap.rgb * 2.0 - 1.0);
    
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(cameraPos - FragPos);

    vec3 ambient = 0.5 * lightColor;  // Luz ambiente fraca

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * specularColor.rgb;

    vec3 result = (ambient + diffuse + specular) * diffuseColor.rgb;

    FragColor = vec4(result, 0.5); 
} 