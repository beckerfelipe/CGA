#ifndef TERRAIN_H
#define TERRAIN_H

#include "Mesh.h"
#include <sstream>
#include <fstream>
#include <stb/stb_image.h>


class Terrain : public Component
{
	//The terrain can have multiple patches, each patch is a mesh
	std::vector<Mesh*> terrainMeshes;

	 void TerrainLoader(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	 void LoadTexture(std::vector<Texture>& textures);
	 unsigned int ReadTexture(std::string name);
	 bool InsideTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 p);


public:
	Terrain();
	void SetShader(Shader* shader);
	void Update();
	float GetHeight(glm::vec2 xz);
	float GetHeight(float x, float z);
};

#endif // !TERRAIN_H
