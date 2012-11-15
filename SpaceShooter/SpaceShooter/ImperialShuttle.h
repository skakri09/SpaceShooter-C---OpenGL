/********************************************************************
    created:    15:11:2012   13:20
    filename:   ImperialStarShuttle.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ImperialShuttle_h__
#define ImperialShuttle_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"

#include "EnemySpaceshipConstantState.h"
#include "ApproachGivenPosition.h"
#include "IdleState.h"
#include "KillOwnerState.h"
#include "ProjectileTypes.h"

class ImperialShuttle : public BaseEnemyShip
{
public:
	ImperialShuttle(std::shared_ptr<PlayerSpaceShip> playerShip, ProjectileTypes cargo);
    ~ImperialShuttle();

	void Update(GLfloat deltaTime);

	void Draw();

	void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

	ProjectileTypes GetCargo(){return cargo;}

private:
	Logger log;

	ProjectileTypes cargo;
};

#endif // ImperialShuttle_h__