#include "MainCamera.h"

Camera* MainCamera::mainCamera = nullptr;

MainCamera::MainCamera(Camera* mainCamera)
{
	this->mainCamera = mainCamera;
}

Camera* MainCamera::GetMainCamera()
{
	return mainCamera;
}

void MainCamera::SetMainCamera(Camera* camera)
{
	mainCamera = camera;
}