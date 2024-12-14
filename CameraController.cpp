#include "CameraController.h"

CameraController::CameraController(Component* parent) : Component(parent)
{
	camera = nullptr;
}

//TODO talvez esse start seja inutil e seja melhor fazer isso direto no construtor
void CameraController::Start()
{
	std::cout << "CameraController Start" << std::endl;
	camera = (Camera*)parent;
	lastMousePosition = InputManager::mousePosition;
}

void CameraController::Update()
{
	float currentFrame = glfwGetTime();
	float deltaTime = currentFrame - timeLastFrame;
	timeLastFrame = currentFrame;

	ProcessKeyboard(deltaTime);
	ProcessMouseMovement(deltaTime);	
}

//TODO melhorar a movimentacao com o mouse
void CameraController::ProcessMouseMovement(float deltaTime)
{
	glm::vec2 mousePosition = InputManager::mousePosition;
	glm::vec2 mouseDelta = mousePosition - lastMousePosition;

	std::cout << mousePosition.x << " " << mousePosition.y << " "<<lastMousePosition.x<<" "<<lastMousePosition.y<<std::endl;

	yaw += mouseDelta.x * mouseSensitivityX * deltaTime;
	pitch += mouseDelta.y * mouseSensitivityY * deltaTime;

	camera->transform.rotation.x = -pitch;
	camera->transform.rotation.y = -yaw;

	lastMousePosition = mousePosition;

}

void CameraController::ProcessKeyboard(float deltaTime)
{
	glm::vec3 forward = Quaternion(0, 0, 0,-1).Rotate(camera->transform.rotation.x, glm::vec3(1, 0, 0)).GetPoint();
	forward = glm::normalize(forward);
	glm::vec3 right = glm::cross(forward, glm::vec3(0, 1, 0));
	right = glm::normalize(right);
	if (InputManager::GetKeyState(GLFW_KEY_W) != InputState::Released)
	{
		camera->transform.position += forward * cameraSpeed * deltaTime;
	}
	if (InputManager::GetKeyState(GLFW_KEY_S) != InputState::Released)
	{
		camera->transform.position += -forward * cameraSpeed * deltaTime;
	}
	if (InputManager::GetKeyState(GLFW_KEY_A) != InputState::Released)
	{
		camera->transform.position += -right * cameraSpeed * deltaTime;
	}
	if (InputManager::GetKeyState(GLFW_KEY_D) != InputState::Released)
	{
		camera->transform.position += right * cameraSpeed * deltaTime;
	}
	if (InputManager::GetKeyState(GLFW_KEY_Q) != InputState::Released)
	{
		camera->transform.position += glm::vec3(0, 1, 0) * cameraSpeed * deltaTime;
	}
	if (InputManager::GetKeyState(GLFW_KEY_E) != InputState::Released)
	{
		camera->transform.position += glm::vec3(0, -1, 0) * cameraSpeed * deltaTime;
	}
}

void CameraController::Destroy()
{

}
