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
static const float PLAYER_XY_VELOCITY = 75.1f;
static const float PLAYER_Z_VELOCITY = 100.0f;

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
	
private:
	Logger log;

};
	
#endif // PlayerSpaceShip_H
