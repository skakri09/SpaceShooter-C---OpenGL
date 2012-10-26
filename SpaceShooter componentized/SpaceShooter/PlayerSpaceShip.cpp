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
	
	
	glRotatef(180, 0, 0, 1);//sortof placeholder rotation
	SpaceShip::Draw();

	glPopMatrix();

	shooterModule.DrawModule();
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
	float dirVecX, float dirVecY, float dirVecZ, float scale)
{
	SpaceShip::InitSpaceShip(startX, startY, startZ, 
		startRotDeg, rotX, rotY, rotZ, 
		dirVecX, dirVecY, dirVecZ, 
		scale);
	
	CreateGameObject("MilleniumFalcon//MilleniumFalcon.3ds");
}

