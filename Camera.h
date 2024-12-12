#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"
#include "Transform.h"
#include <vector>

enum class ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Component
{
public:
	Transform transform;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewProjectionMatrix;

	Camera(ProjectionType projectionType, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	~Camera();
	void Update();
	void AddComponent(Component* component);

private:
	ProjectionType projectionType;
	float fieldOfView;
	float aspectRatio;
	float nearPlane;
	float farPlane;

	glm::vec3 worldUp;

	void UpdateProjectionMatrix();
	void UpdateViewMatrix();
	void UpdateViewProjectionMatrix();
};

#endif // CAMERA_H