#include "KnightController.h"

KnightController::KnightController(Component* parent, Terrain* terrain, NavigationMesh* navigationMesh, Player* player, Camera* deathCamera) : Component(parent)
{
	timeLastFrame = glfwGetTime();
	this->knight = parent;
	this->terrain = terrain;
	this->navigationMesh = navigationMesh;
	this->player = player;
	this->deathCamera = deathCamera;
	currentNode = 20;
	nextNode = 17;
	knight->SetPosition(navigationMesh->nodePosition[currentNode]);
}

void KnightController::Update()
{
	ApplyMovement();
	if (glm::distance(knight->GetPosition(), player->GetPosition()) < 3)
	{
		MainCamera::SetMainCamera(deathCamera);
	}
}

glm::vec3 KnightController::Seek(glm::vec3 target)
{
	glm::vec3 desiredVelocity = glm::normalize(target - knight->GetPosition()) * speed;
	return desiredVelocity - velocity;
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

	float angle = atan2(direction.x, direction.z);

	// Aplica a rotação ao cavaleiro
	knight->SetRotation(glm::vec3(0.0f, angle, 0.0f));
}