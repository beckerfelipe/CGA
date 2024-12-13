#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum State
{
	Released,
	Pressed,
	Repeat
};


class InputManager
{
public:
	static State keys[1024];
	static State mouseButtons[8];
	static glm::vec2 mousePosition;
	static glm::vec2 mouseScroll;
	GLFWwindow* window;

	InputManager(GLFWwindow* window);
	~InputManager();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	static State GetKeyState(int key);
	static State GetMouseButtonState(int button);
};

#endif // !INPUT_MANAGER_H