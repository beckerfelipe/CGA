#ifndef KNIGHT_CONTROLLER_H
#define KNIGHT_CONTROLLER_H

#include "Player.h"
#include "NavigationMesh.h"

class KnightController : public Component
{
	Component* knight;
	NavigationMesh* navigationMesh;
	Terrain* terrain;
	Player* player; 
	Camera* deathCamera;
	float speed = 1.0f; 
	float timeLastFrame = 0.0f;
	glm::vec3 velocity;
	int currentNode;
	int nextNode;

	void ApplyMovement();
	glm::vec3 Seek(glm::vec3 target);

public:
	KnightController(Component* parent, Terrain* terrain, NavigationMesh* NavigationMesh, Player* player, Camera* deathCamera);
	void Update();
};

#endif // !KNIGHT_CONTROLLER_H
