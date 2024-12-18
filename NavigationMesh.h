#ifndef NAVIGATION_MESH_H
#define NAVIGATION_MESH_H

#include "Terrain.h"
#include <fstream>
#include <filesystem>


#define inf 0x3f3f3f3f

class NavigationMesh
{
	int totalNodes;
	float terrainScale;
	Terrain* terrain;

	void ReadGraph(std::string path);
	void CalculatePaths();
	std::vector<std::vector<int>> graph;
	std::vector<std::vector<double>> distance;

public:
	// given node A and node B, nextNode[A][B] will return the next node to go from A to B
	std::vector<std::vector<int>> nextNode;
	std::vector<glm::vec3> nodePosition;
	NavigationMesh(std::string path, Terrain* terrain, float terrainScale);
	int GetNextNode(int currentNode, int lastNode);
};

#endif // !NAVIGATION_MESH_H