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

	if (distance <= 1)
	{
		int aux = nextNode;
		nextNode = navigationMesh->GetNextNode(nextNode, currentNode);
		currentNode = aux;
		std::cout << "trocou " << currentNode << " -> " << nextNode << std::endl;
		return;
	}
	
	glm::vec3 direction = glm::normalize(navigationMesh->nodePosition[nextNode] - knightPosition);

	knightPosition += direction * speed * deltaTime;
	knightPosition.y = terrain->GetHeight(knightPosition.x, knightPosition.z);
	knight->SetPosition(knightPosition);

	glm::vec3 rotation = knight->GetRotation();

	float angle = glm::acos(glm::dot(glm::vec3(0, 1, 0), direction));

	glm::vec3 crossProduct = glm::cross(glm::vec3(0, 1, 0), direction);

	if (crossProduct.y < 0) {
		angle = -angle;
	}

	rotation.y = angle;
	knight->SetRotation(rotation);
}