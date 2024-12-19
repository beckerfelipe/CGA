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
        std::cerr << "Falha ao obter a resolução do monitor!" << std::endl;
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
	mainLoop();
	return 0;
}