#include "Light.h"

glm::vec3 Light:: position;
glm::vec3 Light:: color;
float Light::intensity;

Light::Light()
{
	position = glm::vec3(1000.0f, 1000.0f, 1000.0f);
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;
}

