/********************************************************************
    created:    7:10:2012   9:08
    filename:   SimpleEnemyShip.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SimpleEnemyShip_h__
#define SimpleEnemyShip_h__

#include "SpaceShip.h"
//#include "SimpleEnemyAI.h"

//CD on the spaceships fireing of projectiles in seconds
static const float FIRE_COOLDOWN_SIMPLE_ENEMY  = 0.2f;

//The speed of a square bullet for the player
static const float SQUARE_BULLET_SPEED_SIMPLE_ENEMY = 100.0f;

class SimpleEnemyAI;
class SimpleEnemyShip : SpaceShip
{
public:
    SimpleEnemyShip(SpaceShip* playerShip);
    ~SimpleEnemyShip();

	//Does drawing of the spaceship.
	void Draw();
	//Draws the spaceship and takes care of the bullets it owns
	void Update(GLfloat deltaTime);

	void InitSpaceship(float startX, float startY, float startZ);
	
	//Shoots the gun, calling the fire function from spaceShipbase 
	//with proper parameters (the cd and speed defined in top of class)
	void Shoot();

	const SpaceShip* getPlayerShip(){return playerShip;}
protected:

private:
	Logger log;

	SimpleEnemyAI shipAI; //our AI controlling the ship

	//A pointer to the player spaceship. 
	SpaceShip* playerShip;

	//Creates the displaylist/vbo for the spaceship
	void CreateDrawable();

};
#endif // SimpleEnemyShip_h__