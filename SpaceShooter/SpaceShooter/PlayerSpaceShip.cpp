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
	
	lives = 3;

	activeProjectileType = LASER_FAST;
	
	for(int i = 0; i < totalTypes; i++)
	{
		projTypes[i].projType = static_cast<ProjectileTypes>(i+1);//skipping the first type which is LASER_SLOW
		projTypes[i].known = !i; //all but the first are unknown
	}
	CreateGameObject("MilleniumFalcon//MilleniumFalcon.3ds");
}

ProjectileTypes PlayerSpaceShip::GetActiveProjectileType()
{
	return activeProjectileType;
}

void PlayerSpaceShip::SetActiveProjectileType( ProjectileTypes newType )
{
	for(unsigned int i = 0; i < totalTypes; i++)
	{
		if(projTypes[i].projType == newType)
		{
			if(projTypes[i].known)
			{
				activeProjectileType = newType;
			}
		}
	}
}

bool PlayerSpaceShip::ProjectileTypeKnown( ProjectileTypes projType )
{
	for(int i = 0; i < totalTypes; i++)
	{
		if(projTypes[i].projType == projType)
		{
			if(projTypes[i].known)
			{
				return true;
			}
			return false;
		}
	}
	return false;
}

void PlayerSpaceShip::MakeProjectileActive( ProjectileTypes projType )
{
	for(int i = 0; i < totalTypes; i++)
	{
		if(projTypes[i].projType == projType)
		{
			projTypes[i].known = true;
		}
	}
}
