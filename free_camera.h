#ifndef _FREE_CAMERA_H
#define _FREE_CAMERA_H

#include "camera.h"

class FreeCamera : public Camera : public gef::Application
{
public:
	FreeCamera();
	//inline virtual ~FreeCamera() {}

	void CameraControll(const float frame_time);
};

#endif