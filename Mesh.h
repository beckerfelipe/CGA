#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include "Component.h"
#include "Shader.h"
#include <vector>
#include <string>

enum class TextureType
{
	Diffuse,
	Specular,
	Normal,
	Height
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh : public Component
{
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;
	GLuint VAO, VBO, EBO;

	Shader* shader;

	void SetupMesh();

public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& texture);
	void SetShader(Shader* shader);
	void Update();
};

#endif // !MESH_H
