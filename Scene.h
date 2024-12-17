#ifndef SCENE_H
#define SCENE_H

#include "Shader.h"
#include "Terrain.h"
#include "River.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Quaternion.h"
#include "InputManager.h"
#include "MainCamera.h"
#include "Shader.h"
#include "CameraController.h"

extern double PI;

class Scene
{
	std::vector<Component*> gameObjects;
	void AddGameObjects();
	float GetAspectRation();
public:
	void Render();
	Scene();
	~Scene();
};

#endif // !SCENE_H
