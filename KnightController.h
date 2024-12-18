#ifndef KNIGHT_CONTROLLER_H
#define KNIGHT_CONTROLLER_H

#include "Terrain.h"
#include "NavigationMesh.h"

class KnightController : public Component
{
	Component* knight;
	NavigationMesh* navigationMesh;
	Terrain* terrain;

	float speed = 5.0f; 
	float timeLastFrame = 0.0f;
	//TODO no momento so move entre nós adjacentes,adicionar variavel para poder ir para qualquer no a partir do atual
	int currentNode;
	int nextNode;

	void ApplyMovement();

public:
	KnightController(Component* parent, Terrain* terrain, NavigationMesh* NavigationMesh);
	void Update();
};

#endif // !KNIGHT_CONTROLLER_H
