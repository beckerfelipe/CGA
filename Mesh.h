#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include "Component.h"
#include "Shader.h"
#include <vector>
#include <string>
#include "MainCamera.h"
#include "Transform.h"

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
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;
private:
	GLuint VAO, VBO, EBO;

	Shader* shader;

	void SetupMesh();

public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& texture);
	void SetShader(Shader* shader);
	void Update();
	void UpdateMatrix(glm::mat4 parentWorldMatrix);
};

#endif // !MESH_H
