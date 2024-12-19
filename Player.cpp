#include "Player.h"	

Player::Player(Terrain* terrain, Component* knight)
{
	camera = MainCamera::GetMainCamera();
	this->terrain = terrain;
	this->knight = knight;
	this->AddComponent(camera);
}

void Player::Update()
{
	float deltaTime = glfwGetTime()-lastFrameTime;
	Component::Update();
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
	ProcessKeyboardMovement(deltaTime);
	transform.position.y = terrain->GetHeight(transform.position.x, transform.position.z) + 2;
	camera->SetPosition(transform.position);
	lastFrameTime = glfwGetTime();
}

void Player::ProcessKeyboardMovement(float deltaTime)
{
    float speed = playerSpeed;
	if (InputManager::GetKeyState(GLFW_KEY_LEFT_SHIFT) != InputState::Released)
	{
		speed *= 2;
	}
    if (InputManager::GetKeyState(GLFW_KEY_W) != InputState::Released)
    {
        transform.position += camera->forward * speed ;
    }
    if (InputManager::GetKeyState(GLFW_KEY_S) != InputState::Released)
    {
        transform.position -= camera->forward * speed ;
    }
    if (InputManager::GetKeyState(GLFW_KEY_A) != InputState::Released)
    {
        transform.position -= camera->right * speed ;
    }
    if (InputManager::GetKeyState(GLFW_KEY_D) != InputState::Released)
    {
        transform.position += camera->right * speed ;
    }
}
