#include "Component.h"

Component::Component()
{
	this->parent = nullptr;
}

Component::Component(Component* object)
{
	this->parent = object;
}

void Component::AddComponent(Component* component)
{
	components.push_back(component);
}

void Component::Start()
{
	for (Component* component : components)
	{
		component->Start();
	}
}

void Component::Update()
{
	for (Component* component : components)
	{
		component->Update();
	}
}

void Component::Destroy()
{
	for (Component* component : components)
	{
		component->Destroy();
	}
}