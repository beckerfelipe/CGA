#include "Component.h"
#include <iostream>
Component::Component()
{
	this->parent = nullptr;
	this->transform = Transform();
	this->modelMatrix = glm::mat4(1.0f);
	this->worldModelMatrix = glm::mat4(1.0f);
	this->worldParent = glm::mat4(1.0f);
}

Component::Component(Component* object)
{
	this->parent = object;
	this->transform = Transform();
	this->modelMatrix = glm::mat4(1.0f);
	this->worldModelMatrix = glm::mat4(1.0f);
	this->worldParent = glm::mat4(1.0f);
}

void Component::AddComponent(Component* component)
{
	components.push_back(component);
}

void Component::UpdateMatrix(glm::mat4 parentWorldMatrix)
{
	worldParent = parentWorldMatrix;
}

void Component::Start()
{
	for (Component* component : components)
	{
		component->Start();
	}
}

void Component::UpdateLocalMatrix()
{
	Quaternion forward = Quaternion(transform.rotation.x, glm::vec3(1, 0, 0));
	Quaternion up = Quaternion(transform.rotation.y, glm::vec3(0, 1, 0));
	Quaternion right = Quaternion(transform.rotation.z, glm::vec3(0, 0, 1));

	Quaternion rotation = forward * up * right;

	modelMatrix = glm::translate(glm::mat4(1.0f), transform.position) * rotation.ToMatrix() * glm::scale(glm::mat4(1.0f), transform.scale);

	worldModelMatrix = worldParent * modelMatrix;
}

void Component::Update()
{
	UpdateLocalMatrix();

	for (Component* child : components)
	{
		child->UpdateMatrix(worldModelMatrix);
		child->Update();
	}
}

glm::vec3 Component::GetPosition()
{
	return transform.position;
}

glm::vec3 Component::GetRotation()
{
	return transform.rotation;
}

void Component::SetPosition(glm::vec3 position)
{
	transform.position = position;
	UpdateLocalMatrix();
}

void Component::SetScale(glm::vec3 scale)
{
	transform.scale = scale;
	UpdateLocalMatrix();
}

void Component::SetRotation(glm::vec3 rotation)
{
	transform.rotation = rotation;
	UpdateLocalMatrix();
}

void Component::Destroy()
{
	for (Component* component : components)
	{
		component->Destroy();
	}
}