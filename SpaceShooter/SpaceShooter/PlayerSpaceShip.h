/********************************************************************
*	Created:	2012/09/10  19:42
*	Filename: 	PlayerSpaceShip.h
*	Author:		Kristian Skarseth
*	
*	purpose:	Space ship class for a player controller spaceship.
*********************************************************************/
#ifndef PlayerSpaceShip_H
#define PlayerSpaceShip_H

#include <vector>

#include "SpaceShip.h"
#include "Logger.h"
#include "Mesh3dsLoader.h"

//velocity values for the player spaceship
static const float PLAYER_X_VELOCITY = 35.0f;
static const float PLAYER_Y_VELOCITY = 30.0f;
static const float PLAYER_Z_VELOCITY = 100.0f;

struct ProjectileKnown
{
	ProjectileTypes projType;
	bool known;
};
class PlayerSpaceShip : public SpaceShip
{
public:
	PlayerSpaceShip();
	virtual ~PlayerSpaceShip();

	//Does drawing of the spaceship.
	void Draw();

	//Updates the spaceship
	void Update(GLfloat deltaTime);

	void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);
	
	//Returns the projectile type that's currently active for the player
	ProjectileTypes GetActiveProjectileType();

	//Sets the active projectile type of the player, if it's available
	void SetActiveProjectileType(ProjectileTypes newType);

	bool ProjectileTypeKnown(ProjectileTypes projType);

	void MakeProjectileActive(ProjectileTypes projType);

private:
	Logger log;

	ProjectileTypes activeProjectileType;

	//Array representing the projectiletypes and if they are known or not
	static const unsigned int totalTypes = 5;
	ProjectileKnown projTypes[totalTypes];
};
	
#endif // PlayerSpaceShip_H
