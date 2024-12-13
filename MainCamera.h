#ifndef MAIN_CAMERA_H
#define MAIN_CAMERA_H

#include "Camera.h"

class MainCamera
{
	static Camera* mainCamera;
public:
	MainCamera(Camera* mainCamera);
	static Camera* GetMainCamera();
	static void SetMainCamera(Camera* camera);
};

#endif // !MAIN_CAMERA_H