#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Quaternion.h"
#include "InputManager.h"
#include "Camera.h"
#include "MainCamera.h"
#include "Shader.h"

double PI= glm::pi<double>();
GLuint VAO, VBO;

void Debug(glm::mat4 m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << m[i][j] << " ";
		}
		std::cout << "\n";
	}
}


Shader* shader = nullptr;
MainCamera* mainCamera = nullptr;

std::vector<GLuint> indices;

void CubeTest()
{
    std::vector<glm::vec3> vertices = {
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f)
    };

    indices = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        4, 5, 1, 1, 0, 4,
        3, 2, 6, 6, 7, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    glEnableVertexAttribArray(0);


    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


    glBindVertexArray(0);
}

int mainLoop()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Game", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "ERRO BRABO\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    InputManager* inputManager = new InputManager(window);

    char shaderName[9] = "CubeTest";
    char directory[10] = "./Shaders";
    shader = new Shader(shaderName, directory);
    CubeTest();

    float rotationAngle = 0.0f;
    float increment = 0.1f;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (inputManager->GetKeyState(GLFW_KEY_A) == State::Pressed)
        {
            MainCamera::GetMainCamera()->transform.position += glm::vec3(-0.1, 0, 0);
            MainCamera::GetMainCamera()->Update();
            std::cout << MainCamera::GetMainCamera()->transform.position.x << " " << MainCamera::GetMainCamera()->transform.position.y << " " << MainCamera::GetMainCamera()->transform.position.z << "\n";
        }
        if (inputManager->GetKeyState(GLFW_KEY_D) == State::Pressed)
        {
            MainCamera::GetMainCamera()->transform.position += glm::vec3(0.1, 0, 0);
            MainCamera::GetMainCamera()->Update();
			std::cout << MainCamera::GetMainCamera()->transform.position.x << " " << MainCamera::GetMainCamera()->transform.position.y << " " << MainCamera::GetMainCamera()->transform.position.z << "\n";
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLubyte*)NULL);

        MainCamera::GetMainCamera()->Update();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

        shader->Use();
        glm::mat4 mvp = MainCamera::GetMainCamera()->projectionViewMatrix * model;
		char name[4] = "mvp";   
        shader->SetUniform(name, mvp);

        glfwSwapBuffers(window);
        glfwPollEvents();

        rotationAngle += increment;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}



int main()
{
	Camera* camera= new Camera(ProjectionType::Perspective, PI/4, 1.0f, 0.1f, 100.0f);
	camera->transform.position = glm::vec3(0, 0, 2);
	camera->Update();
	mainCamera = new MainCamera(camera);
	
	//Assimp::Importer importer;
	mainLoop();
	return 0;
}