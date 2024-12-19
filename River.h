#ifndef RIVER_H
#define RIVER_H

#include "Mesh.h"
#include <stb/stb_image.h>

class River : public Component
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	void RiverLoader(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	void LoadTexture(std::vector<Texture>& textures);
	unsigned int ReadTexture(std::string name);
	void SetBuffers();
	Shader* shader;
	GLuint VAO, VBO, EBO;
public:
	River();
	void SetShader(Shader* shader);
	void Update();
};

#endif // !RIVER_H