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
    ImperialStarDestroyer(std::shared_ptr<PlayerSpaceShip> playerShip);
    ~ImperialStarDestroyer();

	void Update(GLfloat deltaTime);

	void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

protected:
	void Draw();

private:
	Logger log;

};

#endif // ImperialStarDestroyerInactive_h__