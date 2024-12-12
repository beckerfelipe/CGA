#ifndef MESH_H
#define MESH_H

#include "Object.h"
#include <vector>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Mesh : public Object
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

#endif // !MESH_H
