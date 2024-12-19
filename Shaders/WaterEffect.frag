#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;  
in vec3 Normal;

uniform sampler2D texture_diffuse1;    
uniform sampler2D texture_specular1;   
uniform sampler2D texture_normal1;    
uniform vec3 lightPos;                 
uniform vec3 cameraPos;               
uniform vec3 lightColor = vec3(1.0,1.0,1.0);
uniform float time;                   

void main()
{
    vec2 movingTexCoord = TexCoord + vec2(sin(time * 0.5) * 0.5, cos(time * 0.5) * 0.5);
    
    vec4 diffuseColor = texture(texture_diffuse1, TexCoord);
    vec4 specularColor = texture(texture_specular1, TexCoord);
    vec4 normalMap = texture(texture_normal1, movingTexCoord);

    vec3 normal = normalize(normalMap.rgb * 2.0 - 1.0);
    
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(cameraPos - FragPos);

    vec3 ambient = 0.5 * lightColor;  // Luz ambiente fraca

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * specularColor.rgb;

    float transparency = 0.3;  
    vec3 result = (ambient + diffuse + specular) * diffuseColor.rgb;

    FragColor = vec4(result, transparency); 
}
