#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Quaternion.h"
#include "InputManager.h"
#include "Camera.h"
#include "MainCamera.h"
#include "Shader.h"
#include "CameraController.h"
#include "ModelLoader.h"

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
Camera* camera = nullptr;

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

void SetupObjects(float aspectRation)
{
    camera = new Camera(ProjectionType::Perspective, PI / 4, aspectRation, 0.1f, 100.0f);
    camera->AddComponent(new CameraController(camera));
    camera->transform.position = glm::vec3(0, 0, 2);
    mainCamera = new MainCamera(camera);
    camera->Start();
}

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

    SetupObjects(float(mode->width)/mode->height);

    char shaderName[12] = "ModelLoader";
    char directory[10] = "./Shaders";
    shader = new Shader(shaderName, directory);
    CubeTest();
	std::vector<Mesh*> meshes = ModelLoader::LoadModel("./Models/Knight/knight.dae");
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->SetShader(shader);
	}
	std::cout << meshes.size() << std::endl;
    float rotationAngle = 0.0f;
    float increment = 0.1f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->Update();
		}
		camera->Update();

        //glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLubyte*)NULL);

  //      MainCamera::GetMainCamera()->Update();
  //      glm::mat4 model = glm::mat4(1.0f);
  //      model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

        //shader->Use();
  //      glm::mat4 mvp = MainCamera::GetMainCamera()->projectionViewMatrix ;
		////char name[4] = "mvp";   
  //      //shader->SetUniform(name, mvp);

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
	//Assimp::Importer importer;
	mainLoop();
	return 0;
}