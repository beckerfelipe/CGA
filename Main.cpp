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

const int terrainWidth = 1000, terrainHeight = 800;
const int maxCircles=100, circleVertices=10;

std::vector<glm::vec2> circles;

double PI= glm::pi<double>();

struct circle
{
	float radius;
	glm::vec2 position;
	glm::vec4 color;
};

std::vector<glm::vec2> GenerateCircleVertices()
{
	std::vector<glm::vec2> vertices(circleVertices);
	double defaultRadius = 1.0;
	double angle = 0;
	for (int i = 0; i < circleVertices; i++)
	{
		vertices[i] = glm::vec2(defaultRadius * cos(angle), defaultRadius * sin(angle));
		angle += PI / circleVertices;
	}
	return vertices;
}

GLuint circleVAO, circleVBO;

void SetupCircle()
{
	std::vector<glm::vec2> vertices = GenerateCircleVertices();

	glGenVertexArrays(1, &circleVAO);
	glBindVertexArray(circleVAO);

	glGenBuffers(1, &circleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
		
	// glVertexAttribPointer(0, )
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

	InputManager* inputManager= new InputManager(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 1;
}

int main()
{
	/*Quaternion q(0, 0, 1, 0);	
	Quaternion p(PI/2, glm::vec3(0, 0, 1));
	Quaternion p1(PI / 2, glm::vec3(0, 1, 0));
	p =p * p1;
	Quaternion r = q.Rotate(p);
	r.Print();*/
	//Assimp::Importer importer;
	mainLoop();
	return 0;
}