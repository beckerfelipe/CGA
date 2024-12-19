#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "Component.h"
#include "Camera.h"
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
//Script that controls the camera, for now it will be a component
class CameraController : public Component
{
	//The camera reference that will be used to modify the camera transform
	Camera* camera;

	float cameraSpeed = 10.0f;
	float mouseSensitivityX = 10.0f;
	float mouseSensitivityY = 10.0f;
	float timeLastFrame = 0.0f;

	float pitch = 0.0f;
	float yaw = -0.0f;

	glm::vec3 worldUp;

	glm::vec2 lastMousePosition = glm::vec2(0.0f, 0.0f);

	void ProcessKeyboard(float deltaTime);
	void ProcessMouseMovement(float deltaTime);

public:
	CameraController(Component *parent);
	void Update();
	void Destroy();
};

#endif // !1
