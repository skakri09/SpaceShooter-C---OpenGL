#include "PlayerSpaceShip.h"


PlayerSpaceShip::PlayerSpaceShip()
	: log("PlayerSpaceship", ERRORX),
	SpaceShip(50)//the HP
{
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

void PlayerSpaceShip::Draw()
{
	glPushMatrix();
	
	transformable.ApplyGLTransformations();
	glRotatef(180, 0, 0, 1);//rotating the player towards negative z axis
	vboDrawable.Draw();

	glPopMatrix();
}

void PlayerSpaceShip::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);
}

void PlayerSpaceShip::Shoot()
{
	SpaceShip::FireGun(SQUARE_FAST_BULLET);
}

void PlayerSpaceShip::InitSpaceShip( float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceShip(startX, startY, startZ, 
		startRotDeg, rotX, rotY, rotZ, 
		dirVecX, dirVecY, dirVecZ, 
		0.4f);
	
	CreateGameObject("MilleniumFalcon//MilleniumFalcon.3ds");
}

