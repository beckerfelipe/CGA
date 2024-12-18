#include "NavigationMesh.h"

NavigationMesh::NavigationMesh(std::string path, Terrain* terrain, float terrainScale)
{
	this->terrainScale = terrainScale;
	this->terrain = terrain;
	ReadGraph(path);
    CalculatePaths();
}

int NavigationMesh::GetNextNode(int currentNode, int lastNode)
{
	for (int i = 0; i < graph[currentNode].size(); i++)
	{
		if (graph[currentNode][i]!=lastNode)
		{
			return graph[currentNode][i];
		}
	}
	return lastNode;
}

void NavigationMesh::CalculatePaths()
{
	distance.resize(totalNodes);
	nextNode.resize(totalNodes);
	for (int i = 0; i < totalNodes; i++)
	{
		distance[i].resize(totalNodes);
		nextNode[i].resize(totalNodes);
		distance[i].assign(totalNodes, inf);
		nextNode[i].assign(totalNodes, -1);
	}

	for (int i = 0; i < totalNodes; i++)
	{
		distance[i][i] = 0;
		nextNode[i][i] = i;
		for (int j : graph[i])
		{
			assert(j < totalNodes);
			assert(i < totalNodes);
			distance[i][j] = glm::length(nodePosition[i]-nodePosition[j]);
			nextNode[i][j] = j;
		}
	}

	for (int k = 0; k < totalNodes; k++)
	{
		for (int i = 0; i < totalNodes; i++)
		{
			for (int j = 0; j < totalNodes; j++)
			{
				assert(j < totalNodes);
				assert(i < totalNodes);
				assert(k < totalNodes);
				if (distance[i][j] > distance[i][k] + distance[k][j])
				{
					distance[i][j] = distance[i][k] + distance[k][j];
					nextNode[i][j] = nextNode[i][k];
				}
			}
		}
	}
}

void NavigationMesh::ReadGraph(std::string path)
{
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) 
    {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
        return;
    }

    std::string line;

	getline(inputFile, line);
	std::istringstream iss(line);

	iss >> totalNodes;

	graph.resize(totalNodes);
	nodePosition.resize(totalNodes);

    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream ss(line);
        glm::vec3 v;
        int idx = 0;
		ss >> idx;

        ss >> v.x >> v.y >> v.z;
		v *= terrainScale;
		v.y = terrain->GetHeight(v.x, v.z);
		nodePosition[idx] = v;

        int num_neighbors;

        ss >> num_neighbors;
 
        for (int i = 0; i < num_neighbors; ++i) {
            int neighbor;
            ss >> neighbor;
            graph[idx].push_back(neighbor);
        }
    }
}