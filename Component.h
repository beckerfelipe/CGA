#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"
#include <vector>

class Component : public Object
{
protected:
	//The object that this component is attached to
	Component* parent;
	//Components attached to that Component
	//Be careful never to depend on the order of the components
	std::vector<Component*> components;
public:
	Component();
	// Add a reference to the object that this component is attached to
	Component(Component* parent);
	virtual void Start();
	virtual void Update();
	virtual void Destroy();
	virtual void AddComponent(Component* component);
};

#endif	