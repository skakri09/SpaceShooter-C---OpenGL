/********************************************************************
    created:    7:10:2012   12:40
    filename:   SimpleEnemy.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SimpleEnemy_h__
#define SimpleEnemy_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"

#include "EnemySpaceshipConstantState.h"
#include "FireState.h"
#include "IdleState.h"
#include "FollowPlayerState.h"
class SimpleEnemy : public BaseEnemyShip
{
public:
    SimpleEnemy(PlayerSpaceShip* playerShip);
    virtual ~SimpleEnemy();
	
	//Does drawing of the spaceship.
	void Draw();
	//Draws the spaceship and takes care of the bullets it owns
	void Update(GLfloat deltaTime);

	void InitSpaceship(float startX, float startY, float startZ);

	//Shoots the gun, calling the fire function from spaceShipbase 
	//with proper parameters (the cd and speed defined in top of class)
	void Shoot();

protected:
	void HandleAI();

private:
	Logger log;

	//Creates the displaylist/vbo for the spaceship
	void CreateDrawable();
};

#endif // SimpleEnemy_h__