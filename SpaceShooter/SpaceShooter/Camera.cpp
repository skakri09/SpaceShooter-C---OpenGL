#include "Camera.h"

Camera::Camera()
	:log("Camera", WARN)
{
	camYaw=0.0f;
	camPitch=0.0f;
	ctrlMode = NUM_PAD_WITH_MOUSE;
	firstRoundOfMouseDown = true;
}

Camera::~Camera()
{
}


void Camera::RenderCamera()
{
	glRotatef(-camPitch, 1.0f, 0.0f, 0.0f);
	glRotatef(-camYaw, 0.0f, 1.0f, 0.0f);
	skybox.drawSkybox();
	UpdateCamera();	
}

void Camera::Control(float mouseVel, float moveVel, InputManager* input)
{
	float actingMoveVel = moveVel;
	if(input->KeyDownHold(SDLK_LSHIFT))
	{	//Setting camera movement speed to 4x if shift is held down
		actingMoveVel*=4;
	}
	else if(input->KeyDownHold(SDLK_LCTRL))
	{//Setting camera movement speed to 1/4th if shift is held down
		actingMoveVel/=4;
	}
	if(ctrlMode != NONE)
	{		
		if(input->LeftMouseDownHold())
		{
			ControlRotation(mouseVel, actingMoveVel, input);
		}
		else
		{
			if(firstRoundOfMouseDown == false)
			{
				SDL_WarpMouse(orgMouseX,orgMouseY); 
			}
			firstRoundOfMouseDown = true;
			
			SDL_ShowCursor(SDL_ENABLE);
		}

		if(ctrlMode == NUM_PAD_WITH_MOUSE)
		{
			ControlCamNumpad(mouseVel, actingMoveVel, input);
		}
		else if(ctrlMode == WASD_WITH_MOUSE)
		{
			ControlCamWASDSX(mouseVel, actingMoveVel, input);
		}
	}
	
}

void Camera::lockCamera()
{
	if(camPitch>90.0f)
		camPitch=90.0f;
	if(camPitch<-90.0f)
		camPitch=-90.0f;
	if(camYaw<0.0f)
		camYaw+=360.0f;
	if(camYaw>360.0f)
		camYaw-=360.0f;
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
	camPos.setY( camPos.getY() + (sin(rad)*dist) );
}

void Camera::UpdateCamera()
{
	glTranslatef(-camPos.getX(), -camPos.getY(), -camPos.getZ());
	
}

void Camera::SetSkybox( std::string newSkybox )
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

void Camera::ControlCamNumpad(float mouseVel, float moveVel, InputManager* input)
{
	if(input->KeyDownHold(SDLK_KP8))//up
	{
		if(camPitch!=90 && camPitch!=-90)  
		{
			moveCamera(moveVel,0.0);
		}
		moveCameraUp(moveVel,0.0);     
	}
	else if(input->KeyDownHold(SDLK_KP5))//down
	{
		if(camPitch!=90 && camPitch!=-90)
		{
			moveCamera(moveVel,180.0);
		}
		moveCameraUp(moveVel,180.0);
	}              
	if(input->KeyDownHold(SDLK_KP4)) //left
	{
		moveCamera(moveVel,90.0);
	}
	else if(input->KeyDownHold(SDLK_KP6)) //right
	{
		moveCamera(moveVel,270);        
	}

	if(input->KeyDownOnce(SDLK_KP2))//reset camera transform
	{
		camYaw=0.0f;
		camPitch=0.0f;
		camPos.setValues(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z);
	}
}

void Camera::ControlCamWASDSX(float mouseVel, float moveVel, InputManager* input)
{
	if(input->KeyDownHold(SDLK_w))//up
	{
		if(camPitch!=90 && camPitch!=-90)  
		{
			moveCamera(moveVel,0.0);
		}
		moveCameraUp(moveVel,0.0);     
	}
	else if(input->KeyDownHold(SDLK_s))//down
	{
		if(camPitch!=90 && camPitch!=-90)
		{
			moveCamera(moveVel,180.0);
		}
		moveCameraUp(moveVel,180.0);
	}              
	if(input->KeyDownHold(SDLK_a)) //left
	{
		moveCamera(moveVel,90.0);
	}
	else if(input->KeyDownHold(SDLK_d)) //right
	{
		moveCamera(moveVel,270);        
	}

	if(input->KeyDownHold(SDLK_SPACE))
	{
		camPos.setY(camPos.getY() + moveVel);
	}
	else if(input->KeyDownHold(SDLK_x))
	{
		camPos.setY(camPos.getY() - moveVel);
	}
	if(input->KeyDownOnce(SDLK_KP2))//reset camera transform
	{
		camYaw=0.0f;
		camPitch=0.0f;
		camPos.setValues(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z);
	}
}

void Camera::SetCtrlMode( ControlMode newControlMode )
{
	this->ctrlMode = newControlMode;
	firstRoundOfMouseDown = true;
}

void Camera::ResetCamRotation()
{
	camYaw=0.0f;
	camPitch=0.0f;
	SDL_ShowCursor(SDL_ENABLE);
}

void Camera::ControlRotation( float mouseVel, float moveVel, InputManager* input )
{
	int MidX=window_width/2; 
	int MidY=window_height/2;

	SDL_ShowCursor(SDL_DISABLE);

	int tmpx,tmpy;
	if(!firstRoundOfMouseDown)
	{
		SDL_GetMouseState(&tmpx,&tmpy); 
	}
	else
	{
		SDL_GetMouseState(&orgMouseX,&orgMouseY); 
		tmpx = MidX;
		tmpy = MidY;
		firstRoundOfMouseDown = false;
	}

	camYaw+=mouseVel*(MidX-tmpx);   
	camPitch+=mouseVel*(MidY-tmpy); 

	lockCamera();

	SDL_WarpMouse(MidX,MidY);   
}

