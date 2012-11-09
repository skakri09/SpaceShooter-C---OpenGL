#include "PlayerSpaceShip.h"


PlayerSpaceShip::PlayerSpaceShip()
	: log("PlayerSpaceship", ERRORX),
	SpaceShip(50)//the HP
{
	lives = 3;
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

void PlayerSpaceShip::Draw()
{
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	transformable.ApplyGLTransformations();
	glRotatef(180, 0, 0, 1);//rotating the player towards negative z axis
	vboDrawable.Draw();
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void PlayerSpaceShip::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);
}

void PlayerSpaceShip::InitSpaceShip( float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceShip(startX, startY, startZ, 
		startRotDeg, rotX, rotY, rotZ, 
		dirVecX, dirVecY, dirVecZ, 
		0.3f);
	
	CreateGameObject("MilleniumFalcon//MilleniumFalcon.3ds");
}
