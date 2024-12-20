#version 460 core

layout(location = 0) in vec3 aPos;    
layout(location = 1) in vec3 aNormal; 
layout(location = 2) in vec2 aTexCoord; 

out vec2 TexCoord;
out vec3 FragPos;    
out vec3 Normal;  

uniform mat4 model;
uniform mat4 projectionView;

uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform float currentTime;

void main()
{
    vec4 worldPosition = model * vec4(aPos, 1.0);
    FragPos = worldPosition.xyz;

    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    TexCoord = aTexCoord;

    gl_Position = projectionView* worldPosition;
}
