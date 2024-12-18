#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "Component.h"
#include "Camera.h"
#include <cassert>
//Script that controls the camera, for now it will be a component
class CameraController : public Component
{
	//The camera reference that will be used to modify the camera transform
	Camera* camera;

	float cameraSpeed = 20.0f;
	float mouseSensitivityX = 0.05f;
	float mouseSensitivityY = 0.05f;
	float timeLastFrame = 0.0f;

	float pitch = 0.0f;
	float yaw = 0.0f;

	glm::vec2 lastMousePosition = glm::vec2(0.0f, 0.0f);

	void ProcessKeyboard(float deltaTime);
	void ProcessMouseMovement(float deltaTime);

public:
	CameraController(Component *parent);
	void Start();
	void Update();
	void Destroy();
};

#endif // !1
