#include "Camera.h"

Camera::Camera(ProjectionType projectionType, float fieldOfView, float aspectRatio, float nearPlane, float farPlane) : Component()
{
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->projectionType = projectionType;
	this->fieldOfView = fieldOfView;
	this->aspectRatio = aspectRatio;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	this->transform = Transform();
	this->viewMatrix = glm::mat4(1.0f);
	this->projectionMatrix = glm::mat4(1.0f);
	this->projectionViewMatrix = glm::mat4(1.0f);
	UpdateProjectionMatrix();
}

void Camera::AddComponent(Component* component)
{
	components.push_back(component);
	std::cout << "Component added to camera "<<components.size() << std::endl;
}

void Camera::UpdateViewMatrix()
{
	Quaternion forward = Quaternion(transform.rotation.x, glm::vec3(1, 0, 0));
	Quaternion up = Quaternion(transform.rotation.y, glm::vec3(0, 1, 0));
	Quaternion right = Quaternion(transform.rotation.z, glm::vec3(0, 0, 1));

	Quaternion rotation = forward * up * right;

	//In viewMatrix translation comes first
	viewMatrix = rotation.ToMatrix() * glm::translate(glm::mat4(1.0f), -transform.position);

}

void Camera::UpdateProjectionMatrix()
{
	if (projectionType == ProjectionType::Perspective)
	{
		projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
	}
	else
	{
		// projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, nearPlane, farPlane);
	}
}

void Camera::Update()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
	transform.Update();
	UpdateViewMatrix();
	UpdateProjectionViewMatrix();
}

void Camera::UpdateProjectionViewMatrix()
{
	projectionViewMatrix = projectionMatrix * viewMatrix;
}

Camera::~Camera()
{
	for (Component* component : components)
	{
		delete component;
	}
	components.clear();
}
