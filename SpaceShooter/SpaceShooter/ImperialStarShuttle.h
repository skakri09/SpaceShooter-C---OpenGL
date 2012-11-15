/********************************************************************
    created:    15:11:2012   13:20
    filename:   ImperialStarShuttle.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ImperialStarShuttle_h__
#define ImperialStarShuttle_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"

#include "EnemySpaceshipConstantState.h"
#include "ApproachGivenPosition.h"
#include "IdleState.h"
#include "KillOwnerState.h"

class ImperialStarShuttle : public BaseEnemyShip
{
public:
    ImperialStarShuttle(std::shared_ptr<PlayerSpaceShip> playerShip);
    ~ImperialStarShuttle();

	void Update(GLfloat deltaTime);

	void Draw();

	void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

private:
	Logger log;
};

#endif // ImperialStarShuttle_h__