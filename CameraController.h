#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "Component.h"
#include "Camera.h"
//Script that controls the camera, for now it will be a component
class CameraController : public Component
{
	//The camera reference that will be used to modify the camera transform
	Camera* camera;
public:
	void Start();
	void Update();
	void Destroy();
};

#endif // !1
