/********************************************************************
    created:    7:10:2012   12:40
    filename:   ImperialTieInterceptor.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ImperialTieInterceptor_h__
#define ImperialTieInterceptor_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"

#include "EnemySpaceshipConstantState.h"
#include "FireState.h"
#include "IdleState.h"
#include "FollowPlayerState.h"

class ImperialTieInterceptor : public BaseEnemyShip
{
public:
    ImperialTieInterceptor(PlayerSpaceShip* playerShip);
    virtual ~ImperialTieInterceptor();
	
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

#endif // ImperialTieInterceptor_h__