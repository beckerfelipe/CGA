#include "Transform.h"

Transform::Transform()
{
	position = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	rotation = glm::vec3(0.0f);
}

void Transform::UpdateModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	
	//TODO testar ver se esta ok
	Quaternion xRotation = Quaternion(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Quaternion yRotation = Quaternion(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	Quaternion zRotation = Quaternion(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	Quaternion rotationQuaternion = xRotation * yRotation * zRotation;
	modelMatrix = modelMatrix * rotationQuaternion.ToMatrix();

	modelMatrix = glm::scale(modelMatrix, scale);
}

void Transform::Update()
{
	UpdateModelMatrix();
}