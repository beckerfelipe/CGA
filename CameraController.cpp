#include "CameraController.h"

CameraController::CameraController(Component* parent) : Component(parent)
{
    camera = (Camera*)parent;
    lastMousePosition = InputManager::mousePosition;
    timeLastFrame = glfwGetTime();
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}


void CameraController::Update()
{
	glm::vec3 p = camera->transform.position;
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - timeLastFrame;
    timeLastFrame = currentFrame;

    // Processa entradas do teclado e mouse.
    ProcessKeyboard(deltaTime);
    ProcessMouseMovement(deltaTime);
}

void CameraController::ProcessMouseMovement(float deltaTime)
{
    glm::vec2 mousePosition = InputManager::mousePosition;
    glm::vec2 mouseDelta = mousePosition - lastMousePosition;

    // Atualiza os ângulos de rotação com base na sensibilidade.
    yaw += mouseDelta.x * mouseSensitivityX* deltaTime;
    pitch -= mouseDelta.y * mouseSensitivityY* deltaTime; // Invertemos o eixo Y para comportamento padrão.

    // Limita o pitch para evitar que a câmera "gire de ponta-cabeça".
    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    lastMousePosition = mousePosition;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera->forward = glm::normalize(front);
	camera->right = glm::normalize(glm::cross(camera->forward, worldUp));
	camera->up = glm::normalize(glm::cross(camera->right, camera->forward));
}

void CameraController::ProcessKeyboard(float deltaTime)
{
    // Movimenta a câmera com base nas teclas pressionadas.
    if (InputManager::GetKeyState(GLFW_KEY_W) != InputState::Released)
    {
        camera->transform.position += camera->forward * cameraSpeed * deltaTime;
    }
    if (InputManager::GetKeyState(GLFW_KEY_S) != InputState::Released)
    {
        camera->transform.position -= camera->forward * cameraSpeed * deltaTime;
    }
    if (InputManager::GetKeyState(GLFW_KEY_A) != InputState::Released)
    {
        camera->transform.position -= camera->right * cameraSpeed * deltaTime;
    }
    if (InputManager::GetKeyState(GLFW_KEY_D) != InputState::Released)
    {
        camera->transform.position += camera->right * cameraSpeed * deltaTime;
    }
    if (InputManager::GetKeyState(GLFW_KEY_Q) != InputState::Released)
    {
        camera->transform.position += worldUp * cameraSpeed * deltaTime;
    }
    if (InputManager::GetKeyState(GLFW_KEY_E) != InputState::Released)
    {
        camera->transform.position -= worldUp * cameraSpeed * deltaTime;
    }
}


void CameraController::Destroy()
{

}
