#ifndef PLAYER_H
#define PLAYER_H

#include "Terrain.h"
#include "Camera.h"
#include "InputManager.h"

class Player : public Component
{
	Terrain* terrain;
	Camera* camera;
	Component* knight;

	float lastFrameTime = 0.0f;
	float playerSpeed = 0.5f;

	void ProcessKeyboardMovement(float deltaTime);
public:
	Player(Terrain* terrain, Component* component);
	void Update();
};

#endif // !PLAYER_H
