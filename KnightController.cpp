#include "KnightController.h"

KnightController::KnightController(Component* parent, Terrain* terrain, NavigationMesh* navigationMesh) : Component(parent)
{
	timeLastFrame = glfwGetTime();
	this->knight = parent;
	this->terrain = terrain;
	this->navigationMesh = navigationMesh;
	currentNode = 20;
	nextNode = 17;
	knight->SetPosition(navigationMesh->nodePosition[currentNode]);
}

void KnightController::Update()
{
	ApplyMovement();
}

void KnightController::ApplyMovement()
{
	float deltaTime = glfwGetTime() - timeLastFrame;
	timeLastFrame = glfwGetTime();

	glm::vec3 knightPosition = knight->GetPosition();

	double distance = glm::distance(knightPosition, navigationMesh->nodePosition[nextNode]);

	std::cout << knightPosition.x << " " << knightPosition.y << " " << knightPosition.z << "  -  " << navigationMesh->nodePosition[nextNode].x << " " << navigationMesh->nodePosition[nextNode].y << " " << navigationMesh->nodePosition[nextNode].z << std::endl;
	if (distance <= 1)//TODO aumentar aqui ou descobrir o porque do sample height estar retornando valores diferentes
	{
		int aux = nextNode;
		nextNode = navigationMesh->GetNextNode(nextNode, currentNode);
		currentNode = aux;
		std::cout << "trocou " << currentNode << " -> " << nextNode << std::endl;
		return;
	}
	
	glm::vec3 direction = glm::normalize(navigationMesh->nodePosition[nextNode] - knightPosition);
	//isso aqui pode causar problemas quando se aproxima de um no
	knightPosition += direction * speed * deltaTime;
	knightPosition.y = terrain->GetHeight(knightPosition.x, knightPosition.z);
	knight->SetPosition(knightPosition);
}