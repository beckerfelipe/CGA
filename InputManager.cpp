#include "InputManager.h"
#include <iostream>

State InputManager::keys[1024] = { State::Released };
State InputManager::mouseButtons[8] = { State::Released };
glm::vec2 InputManager::mousePosition = glm::vec2(0.0f, 0.0f);
glm::vec2 InputManager::mouseScroll = glm::vec2(0.0f, 0.0f);

InputManager::InputManager(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this); //TODO: entender como isso funciona
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	this->window = window;

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	mousePosition = glm::vec2(width / 2, height / 2);
	mouseScroll = glm::vec2(0.0f);
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if(inputManager!=nullptr)
	{
		std::cout << "Key: " << key << " Action: " << action << std::endl;
		inputManager->keys[key] = (State)(action ^ GLFW_PRESS ^ GLFW_RELEASE ^ GLFW_REPEAT);
	}
}

void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (inputManager != nullptr)
	{
		inputManager->mousePosition = glm::vec2(xpos, ypos);
	}
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (inputManager != nullptr)
	{
		std::cout << "Button: " << button << " Action: " << action << std::endl;
		inputManager->mouseButtons[button] = (State)(action ^ GLFW_PRESS ^ GLFW_RELEASE ^ GLFW_REPEAT);
	}
}

void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (inputManager != nullptr)
	{
		inputManager->mouseScroll = glm::vec2(xoffset, yoffset);
	}
}

InputManager::~InputManager()
{
}