/********************************************************************
    created:    7:10:2012   12:40
    filename:   SimpleEnemy.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SithInfiltrator_h__
#define SithInfiltrator_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"

#include "EnemySpaceshipConstantState.h"
#include "FireState.h"
#include "IdleState.h"
#include "ApproachXYZPlayerState.h"
#include "ApproachXYPlayerState.h"
class SithInfiltrator : public BaseEnemyShip
{
public:
    SithInfiltrator(PlayerSpaceShip* playerShip);
    virtual ~SithInfiltrator();
	
	//Does drawing of the spaceship.
	void Draw();
	//Draws the spaceship and takes care of the bullets it owns
	void Update(GLfloat deltaTime);

	void InitSpaceship(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

	//Shoots the gun, calling the fire function from spaceShipbase 
	//with proper parameters (the cd and speed defined in top of class)
	void Shoot();

protected:
	void HandleAI();

private:
	Logger log;

	//Creates the displaylist/vbo for the spaceship
	void CreateGameObject();
};

#endif // SithInfiltrator_h__