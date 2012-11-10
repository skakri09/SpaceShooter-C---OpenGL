/********************************************************************
    created:    10:11:2012   13:18
    filename:   Camera.h
    author:     Kristian Skarseth
    
    purpose:    Camera class. Allows us to move around in our scene, or
				more correctly said, move everything arround in the scene.
				Also holds the skybox

	Note:		Inspiration for the class gotten from  a tutorial by 
				thecplusplusguy at youtube
*********************************************************************/
#ifndef Camera_h__
#define Camera_h__

//defining pi if it's not defined in cmath
#ifndef M_PI
#define M_PI 3.1415926535f
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
#include "Vector3d.h"

class Camera
{
public:
	Camera();
	~Camera();

	void RenderCamera();

	//Set the position of the camera based on input from user.
	void Control(float mouseVel, float moveVel, InputManager* input);

	//Sets the position manually
	void SetCameraPosition(Vector3D* position);
	void SetCameraPosition(float xPos, float yPos, float zPos);

	//Updates the camera automatically. The camera will move slightly
	//in various directions to give some depth to whatever is shown
	void UpdateAutomaticCamera(float deltaTime);

	//Change the skybox
	void ChangeSkybox(std::string newSkybox);

private:
	Skybox skybox;

	//Locks the camera between 90 and 0 for pitch,
	//and 360 and 0 for yaw
	void lockCamera();

	void moveCamera(float dist, float dir);
	void moveCameraUp(float dist, float dir);
	
	//Sets the movement translation
	void UpdateCamera();

	Vector3D camPos;		//current camera position
	float camYaw;			//camera rotation in Y axis
	float camPitch;			//camera rotation in X axis

};

#endif // Camera_h__