#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Quaternion.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
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
