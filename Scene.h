#ifndef SCENE_H
#define SCENE_H

#include "Shader.h"
#include "Terrain.h"
#include "River.h"
#include "ModelLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Quaternion.h"
#include "InputManager.h"
#include "MainCamera.h"
#include "Shader.h"
#include "CameraController.h"
#include "NavigationMesh.h"
#include "KnightController.h"	
#include "Light.h"

extern double PI;

class Scene
{
	std::vector<Component*> gameObjects;
	//Terrain reference stored in gameObjects
	Terrain* terrain;
	Component* knight;
	Camera* camera;

	NavigationMesh* navigationMesh;

	float terrainScale = 2.0f;

	void AddGameObjects();
	float GetAspectRation();
	void LoadHouses();
	void GetHousePositions(std::vector<glm::vec3>& positionsA, std::vector<glm::vec3>& positionsB, std::vector<glm::vec3>& positionsC);
	void LoadKnight();
	void LoadTrees();
	void GetHousePositions(std::vector<glm::vec3>& positions);

public:
	void Render();
	Scene();
	~Scene();
};

#endif // !SCENE_H
