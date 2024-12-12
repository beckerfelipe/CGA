#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Quaternion.h"

class Transform : public Component
{
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	Transform();
	void Update();
private:
	glm::mat4 modelMatrix;
	void UpdateModelMatrix();
	
};

#endif // TRANSFORM_H
