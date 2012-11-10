#include "Camera.h"

Camera::Camera()
{
	camYaw=0.0f;
	camPitch=0.0f;
}

Camera::~Camera()
{
}


void Camera::RenderCamera()
{
	glRotatef(-camPitch,1.0,0.0,0.0);
	glRotatef(-camYaw,0.0,1.0,0.0);
	skybox.drawSkybox();
	UpdateCamera();	
}

void Camera::Control(float mouseVel, float moveVel, InputManager* input)
{
	if(input->LeftMouseDownHold())
	{
		int MidX=window_width/2;
		int MidY=window_height/2;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx,tmpy;
		SDL_GetMouseState(&tmpx,&tmpy);
		camYaw+=mouseVel*(MidX-tmpx);
		camPitch+=mouseVel*(MidY-tmpy);
		lockCamera();
		SDL_WarpMouse(MidX,MidY);
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
	}

	if(input->MoveUp())
	{
		if(camPitch!=90 && camPitch!=-90)
			moveCamera(moveVel,0.0);
		moveCameraUp(moveVel,0.0);
	}
	else if(input->MoveDown())
	{
		if(camPitch!=90 && camPitch!=-90)
			moveCamera(moveVel,180.0);
		moveCameraUp(moveVel,180.0);
	}		

	if(input->MoveLeft())
		moveCamera(moveVel,90.0);
	else if(input->MoveRight())
		moveCamera(moveVel,270);	
}

void Camera::lockCamera()
{
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
	float rad=(camYaw+dir)*M_PI/180.0f;

	camPos.setX( camPos.getX() - (sin(rad)*dist) );
	camPos.setZ( camPos.getZ() - (cos(rad)*dist) );
}

void Camera::moveCameraUp(float dist,float dir)
{
	float rad=(camPitch+dir)*M_PI/180.0f;
	camPos.setZ( camPos.getZ() + (sin(rad)*dist) );
}

void Camera::UpdateCamera()
{
	glTranslatef(-camPos.getX(), -camPos.getY(), -camPos.getZ());
}

void Camera::ChangeSkybox( std::string newSkybox )
{
	skybox.initSkybox(newSkybox, 10);
}

void Camera::UpdateAutomaticCamera( float deltaTime )
{

}

void Camera::SetCameraPosition( Vector3D* position )
{
	camPos = *position;
}

void Camera::SetCameraPosition( float xPos, float yPos, float zPos )
{
	camPos.setValues(xPos, yPos, zPos);
}
