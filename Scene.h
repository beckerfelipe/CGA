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
#include "Player.h"
#include <set>
#include "Cube.h"
extern double PI;

class Scene
{
	std::vector<Component*> gameObjects;
	std::multiset<Component*> secretHouse;

	//Terrain reference stored in gameObjects
	Terrain* terrain;
	Component* knight;
	Camera* camera;
	Camera* secundaryCamera;
	Player* player;
	River* river;
	NavigationMesh* navigationMesh;
	Cube* cube;

	float terrainScale = 2.0f;
	float maxDistanceCulling = 200.0f;
	float lastFrameTime = 0.0f;
	float accumulator = 0.0f;
	bool ok = 0;
	int FPS = 60;

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
