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
//CD on the spaceships fireing of projectiles in seconds
static const float FIRE_COOLDOWN_PLAYER  = 0.2f;

//The speed of a square bullet for the player
static const float SQUARE_BULLET_SPEED_PLAYER = 100.0f;


class PlayerSpaceShip : public SpaceShip
{
public:
	PlayerSpaceShip();
	virtual ~PlayerSpaceShip();

	//Does drawing of the spaceship.
	void Draw();
	//Draws the spaceship and takes care of the bullets it owns
	void Update(GLfloat deltaTime);

	void InitSpaceship(float startX, float startY, float startZ,
		float scaleX, float scaleY, float scaleZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

	//Shoots the gun, calling the fire function from spaceShipbase 
	//with proper parameters (the cd and speed defined in top of class)
	void Shoot();
	
private:
	Logger log;

	//Creates the displaylist or VBO for the spaceship
	void CreateDrawable();

};
	
#endif // PlayerSpaceShip_H
