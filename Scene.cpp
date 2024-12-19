#include "Scene.h"

static double PI= glm::pi<double>();

Scene::Scene()
{
	Light();
	AddGameObjects();
}


void Scene::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

float Scene::GetAspectRation()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        std::cerr << "Falha ao obter o monitor!" << std::endl;
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) {
        std::cerr << "Falha ao obter a resolução do monitor!" << std::endl;
        return -1;
    }

	return float(mode->width) / float(mode->height);
}

void Scene::AddGameObjects()
{
    char directory[10] = "./Shaders";

    terrain = new Terrain();
    Shader* s1 = new Shader((char*)"Terrain", directory);
    terrain->SetShader(s1);
	terrain->SetScale(glm::vec3(terrainScale, terrainScale, terrainScale));

	gameObjects.push_back(terrain);

	navigationMesh = new NavigationMesh("./TerrainData/NavigationMesh.txt", terrain, terrainScale);

    River* river = new River();
	river->SetScale(glm::vec3(terrainScale, terrainScale, terrainScale));
    Shader* s2 = new Shader((char*)"WaterEffect", directory);
    river->SetShader(s2);
	gameObjects.push_back(river);

	LoadHouses();

	LoadTrees();

	LoadKnight(); 

	float aspectRation = GetAspectRation();
	if (aspectRation == -1)
	{
		std::cerr << "Falha ao obter a resolução do monitor!" << std::endl;
		exit(1);
	}
	camera = new Camera(ProjectionType::Perspective, PI / 4, aspectRation, 0.1f, 50.0f);
	camera->AddComponent(new CameraController(camera));
	camera->transform.position = glm::vec3(0, terrain->GetHeight(100,100)+10, 20);
	std::cout << "camera position: " << camera->transform.position.x << " " << camera->transform.position.y << " " << camera->transform.position.z << std::endl;
	MainCamera* mainCamera = new MainCamera(camera);

	gameObjects.push_back(camera);

}

void Scene::LoadKnight()
{
	std::vector<Mesh*> models = ModelLoader::LoadModel((char*)"./Models/Knight/Knight.dae");
	knight = new Component();
	Shader* shader = new Shader((char*)"ModelLoader", (char*)"./Shaders");
	for (int i = 0; i < models.size(); i++)
	{
		models[i]->SetShader(shader);
		knight->AddComponent(models[i]);
	}
	knight->SetScale(glm::vec3(0.01, 0.01, 0.01));
	knight->SetPosition(glm::vec3(0, terrain->GetHeight(0, -100), -100));
	gameObjects.push_back(knight);

	Component* knightController = new KnightController(knight, terrain, navigationMesh);
	knight->AddComponent(knightController);
}

void Scene::LoadTrees()
{
	std::vector<glm::vec3> positions;
	GetHousePositions(positions);
	Shader* shader = new Shader((char*)"ModelLoader", (char*)"./Shaders");
	std::vector<Mesh*> models = ModelLoader::LoadModel((char*)"./Buildings/Trees/Pine_4m.dae");
	for (int i = 0; i < positions.size(); i++)
	{
		positions[i] *= terrainScale;
		positions[i].y = terrain->GetHeight(positions[i].x, positions[i].z)+1;
		Component* tree = new Component();
		tree->SetPosition(positions[i]);
		tree->SetRotation(glm::vec3(PI / 2, 0, 0));
		glm::vec3 scale = glm::vec3(0.05,0.05,0.05);
		tree->SetScale(scale);
		for (int j = 0; j < models.size(); j++)
		{
			models[j]->SetShader(shader);
			tree->AddComponent(models[j]);
		}
		gameObjects.push_back(tree);
	}
}

void Scene::LoadHouses()
{
	std::vector<glm::vec3> positionsA, positionsB, positionsC;
	GetHousePositions(positionsA, positionsC, positionsB);
	Shader* shader = new Shader((char*)"ModelLoader", (char*)"./Shaders");
	std::vector<Mesh*> models = ModelLoader::LoadModel((char*)"./Buildings/HouseB/HouseB.dae");

	for (int i = 0; i < positionsB.size(); i++)
	{
		positionsB[i] *= terrainScale;
		positionsB[i].y = terrain->GetHeight(positionsB[i].x, positionsB[i].z);
		Component* house = new Component();
		house->SetPosition(positionsB[i]);
		house->SetRotation(glm::vec3(PI/2, 0, 0));
		house->SetScale(glm::vec3(0.5, 0.5, 0.5));
		for (int j = 0; j < models.size(); j++)
		{
			models[j]->SetShader(shader);
			house->AddComponent(models[j]);
		}
		gameObjects.push_back(house);
	}

	models = ModelLoader::LoadModel((char*)"./Buildings/HouseC/HouseC.dae");
	for (int i = 0; i < positionsC.size(); i++)
	{
		positionsC[i] *= terrainScale;
		positionsC[i].y = terrain->GetHeight(positionsC[i].x, positionsC[i].z)+2.5;
		Component* house = new Component();
		house->SetPosition(positionsC[i]);
		house->SetScale(glm::vec3(0.5, 0.5, 0.5));
		for (int j = 0; j < models.size(); j++)
		{
			models[j]->SetShader(shader);
			house->AddComponent(models[j]);
		}
		gameObjects.push_back(house);
	}

	models = ModelLoader::LoadModel((char*)"./Buildings/HouseC/HouseC.dae");
	for (int i = 0; i < positionsA.size(); i++)
	{
		positionsA[i] *= terrainScale;
		positionsA[i].y = terrain->GetHeight(positionsA[i].x, positionsA[i].z) + 1;
		Component* house = new Component();
		house->SetPosition(positionsA[i]);
		house->SetScale(glm::vec3(0.5, 0.5, 0.5));
		for (int j = 0; j < models.size(); j++)
		{
			models[j]->SetShader(shader);
			house->AddComponent(models[j]);
		}
		gameObjects.push_back(house);
	}
}

void Scene::GetHousePositions(std::vector<glm::vec3>& positions)
{
	std::string path = "./TerrainData/treePosition.txt";

	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
		return;
	}

	int verticesA = 0, verticesB = 0, verticesC = 0;

	std::string line;

	if (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> verticesA;
	}
	positions.resize(verticesA);

	int idx = 0;

	for (int i = 0; i < verticesA; ++i) {
		if (std::getline(file, line)) {
			std::istringstream vertexStream(line);
			glm::vec3 v;
			vertexStream >> v.x >> v.y >> v.z;
			positions[idx++] = v;
		}
	}
}

void Scene::GetHousePositions(std::vector<glm::vec3>& positionsA, std::vector<glm::vec3>& positionsB, std::vector<glm::vec3>& positionsC)
{
	
	std::string path = "./TerrainData/HousePositions.txt";
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
		return;
	}

	int verticesA=0, verticesB=0, verticesC = 0;

	std::string line;

	if (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> verticesA;
	}
	positionsA.resize(verticesA);

	int idx = 0;

	for (int i = 0; i < verticesA; ++i) {
		if (std::getline(file, line)) {
			std::istringstream vertexStream(line);
			glm::vec3 v;
			vertexStream >> v.x >> v.y >> v.z;
			positionsA[idx++] = v;
		}
	}

	idx = 0;

	if (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> verticesB;
	}

	positionsB.resize(verticesB);

	for (int i = 0; i < verticesB; ++i) {
		if (std::getline(file, line)) {
			std::istringstream vertexStream(line);
			glm::vec3 v;
			vertexStream >> v.x >> v.y >> v.z;
			positionsB[idx++] = v;
		}
	}

	idx = 0;

	if (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> verticesC;
	}

	positionsC.resize(verticesC);	

	for (int i = 0; i < verticesC; ++i) {
		if (std::getline(file, line)) {
			std::istringstream vertexStream(line);
			glm::vec3 v;
			vertexStream >> v.x >> v.y >> v.z;
			positionsC[idx++] = v;
		}
	}
	

	file.close();

}

Scene::~Scene()
{
}