#include "Camera.h"

Camera::Camera()
{
	camX=0.0f;
	camY=0.0f;
	camZ=0.0f;	
	camYaw=0.0f;
	camPitch=0.0f;
}

Camera::~Camera()
{

}


void Camera::Control(float mousevel, InputManager* input)
{
	if(input->LeftMouseDownHold())	//if the mouse is in the screen
	{
		int MidX=window_width/2;	//middle of the screen
		int MidY=window_height/2;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx,tmpy;
		SDL_GetMouseState(&tmpx,&tmpy);	//get the current position of the cursor
		camYaw+=mousevel*(MidX-tmpx);	//get the rotation, for example, if the mouse current position is 315, than 5*0.2, this is for Y
		camPitch+=mousevel*(MidY-tmpy);	//this is for X
		lockCamera();
		SDL_WarpMouse(MidX,MidY);	//move back the cursor to the center of the screen
		//Uint8* state=SDL_GetKeyState(NULL);	//which key is pressed?
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
	}

	if(input->MoveUp())
	{
		if(camPitch!=90 && camPitch!=-90)	//if we are facing directly up or down, we don't go forward, it will be commented out, when there will be gravity
			moveCamera(mousevel,0.0);	//move forward
		moveCameraUp(mousevel,0.0);	//move up/down
	}
	else if(input->MoveDown())
	{
		//same, just we use 180 degrees, so we move at the different direction (move back)
		if(camPitch!=90 && camPitch!=-90)
			moveCamera(mousevel,180.0);
		moveCameraUp(mousevel,180.0);
	}		

	if(input->MoveLeft())
		moveCamera(mousevel,90.0);
	//else if(state[SDLK_d])	//move right
	else if(input->MoveRight())
		moveCamera(mousevel,270);	
	
	
	
	glRotatef(-camPitch,1.0,0.0,0.0);
	glRotatef(-camYaw,0.0,1.0,0.0);
	skybox.drawSkybox();
	UpdateCamera();
	
}

void Camera::lockCamera()
{
	//set campitch between -90 and 90 and set camyaw between 0 and 360 degrees
	if(camPitch>90)
		camPitch=90;
	if(camPitch<-90)
		camPitch=-90;
	if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360;
}

void Camera::moveCamera(float dist,float dir)
{
	float rad=(camYaw+dir)*M_PI/180.0;	//convert the degrees into radians
	camX-=sin(rad)*dist;	//calculate the new coorinate, if you don't understand, draw a right triangle with the datas, you have
	camZ-=cos(rad)*dist;	//and try to calculate the new coorinate with trigonometric functions, that should help
}

void Camera::moveCameraUp(float dist,float dir)
{
	//the the same, only this time we calculate the y coorinate
	float rad=(camPitch+dir)*M_PI/180.0;
	camY+=sin(rad)*dist;	
}

void Camera::UpdateCamera()
{
	glTranslatef(-camX,-camY,-camZ);	//move the camera
}

void Camera::ChangeSkybox( std::string newSkybox )
{
	skybox.initSkybox(newSkybox, 10);
}
