#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"
#include <vector>
#include "Transform.h"

class Component : public Object
{
protected:
	//The object that this component is attached to
	Component* parent;
	//Components attached to that Component
	//Be careful never to depend on the order of the components
	std::vector<Component*> components;

	glm::mat4 modelMatrix;
	glm::mat4 worldParent;
	glm::mat4 worldModelMatrix;
	Transform transform;
		
	virtual void UpdateMatrix(glm::mat4 worldModelMatrix);
	virtual void UpdateLocalMatrix();

public:
	Component();
	// Add a reference to the object that this component is attached to
	Component(Component* parent);
	virtual void Start();
	virtual void Update();
	virtual void Destroy();
	virtual void AddComponent(Component* component);
	virtual void SetPosition(glm::vec3 position);
	virtual void SetScale(glm::vec3 scale);
	virtual void SetRotation(glm::vec3 rotation);
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetRotation();
};

#endif	