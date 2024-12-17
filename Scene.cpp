#include "Scene.h"

static double PI= glm::pi<double>();

Scene::Scene()
{
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
	float aspectRation = GetAspectRation();
	if (aspectRation == -1)
	{
		std::cerr << "Falha ao obter a resolução do monitor!" << std::endl;
		exit(1);
	}
    Camera* camera = new Camera(ProjectionType::Perspective, PI / 4, aspectRation, 0.1f, 10.0f);
    camera->AddComponent(new CameraController(camera));
    camera->transform.position = glm::vec3(0, 0, 2);
    MainCamera* mainCamera = new MainCamera(camera);
    camera->Start();

    char directory[10] = "./Shaders";

    Terrain* terrain = new Terrain();
    Shader* s1 = new Shader((char*)"Terrain", directory);
    terrain->SetShader(s1);

    River* river = new River();
    Shader* s2 = new Shader((char*)"CubeTest", directory);
    river->SetShader(s2);

	gameObjects.push_back(terrain);
	gameObjects.push_back(river);
	gameObjects.push_back(camera);
}

Scene::~Scene()
{
}