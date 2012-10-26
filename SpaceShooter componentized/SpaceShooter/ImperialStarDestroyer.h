/********************************************************************
    created:    16:10:2012   18:34
    filename:   ImperialStarDestroyer.h
    author:     Kristian Skarseth
    
    purpose:    An imperial star destroyer. Acts as a boss and a ship spawner.
*********************************************************************/
#ifndef ImperialStarDestroyer_h__
#define ImperialStarDestroyer_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"
 #include "StarDestroyerShipSpawning.h"

class ImperialStarDestroyer : public BaseEnemyShip
{
public:
    ImperialStarDestroyer(PlayerSpaceShip* playerShip);
    ~ImperialStarDestroyer();

	//Does drawing of the spaceship.
	void Draw();

	//Draws the spaceship and takes care of the bullets it owns
	void Update(GLfloat deltaTime);

	void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

	//Shoots the gun, calling the fire function from spaceShipbase 
	//with proper parameters (the cd and speed defined in top of class)
	void Shoot();

protected:
	void HandleAI();

private:
	Logger log;

};

#endif // ImperialStarDestroyerInactive_h__