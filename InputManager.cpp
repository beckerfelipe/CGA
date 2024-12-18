#include "InputManager.h"
#include <iostream>

InputState InputManager::keys[1024] = { InputState::Released };
InputState InputManager::mouseButtons[8] = { InputState::Released };
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
		inputManager->keys[key] = (InputState)(action);
		//std::cout << "Key: " << key << " State: " << inputManager->keys[key] << std::endl;
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
		inputManager->mouseButtons[button] = (InputState)(action);
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

InputState InputManager::GetKeyState(int key)
{
	return keys[key];
}

InputState InputManager::GetMouseButtonState(int button)
{
	return mouseButtons[button];
}

InputManager::~InputManager()
{
}