#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
public:

	static glm::vec3 position;
	static glm::vec3 color;
	static float intensity;
	Light();
};

#endif // !LIGHT_H
