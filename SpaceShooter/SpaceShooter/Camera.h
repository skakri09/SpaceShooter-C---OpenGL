/********************************************************************
    created:    10:11:2012   13:18
    filename:   Camera.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Camera_h__
#define Camera_h__

#ifndef M_PI	//if the pi is not defined in the cmath header file
#define M_PI 3.1415926535	//define it
#endif

#include <SDL.h>
#include <GL/glew.h>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "GameConstants.h"
#include "InputManager.h"
#include "Skybox.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Control(float mousevel, InputManager* input);
	void ChangeSkybox(std::string newSkybox);

private:
	Skybox skybox;

	void lockCamera();
	void moveCamera(float,float);
	void moveCameraUp(float,float);
	void UpdateCamera();

	float camX, camY, camZ;	//current position of the camera
	float camYaw;			//camera rotation in Y axis
	float camPitch;			//camera rotation in X axis

};

#endif // Camera_h__