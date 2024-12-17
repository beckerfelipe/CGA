#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "InputManager.h"
#include "Scene.h"


int mainLoop()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        std::cerr << "Falha ao obter o monitor!" << std::endl;
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) {
        std::cerr << "Falha ao obter a resolu��o do monitor!" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Game", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "ERRO BRABO\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    InputManager* inputManager = new InputManager(window);
	Scene* scene = new Scene();

    /*shader = new Shader(shaderName, directory);
	std::vector<Mesh*> meshes = ModelLoader::LoadModel("./Buildings/HouseB/houseB.dae");
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->SetShader(shader);
	}
	std::cout << meshes.size() << std::endl;*/

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
		scene->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}

//talvez a camera esteja bugada porque estou renderizando os objetos no 0,0,0
int main()
{	
	//Assimp::Importer importer;
	mainLoop();
	return 0;
}