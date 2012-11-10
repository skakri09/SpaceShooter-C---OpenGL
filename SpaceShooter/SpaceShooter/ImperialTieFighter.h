/********************************************************************
    created:    12:10:2012   16:08
    filename:   ImperialTieFighter.h
    author:     Kristian Skarseth
    
    purpose:    An imperial tie fighter enemy.
*********************************************************************/
#ifndef ImperialTieFighter_h__
#define ImperialTieFighter_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"

#include "EnemySpaceshipConstantState.h"
#include "FireState.h"
#include "IdleState.h"
#include "ApproachRandXYPos.h"

class ImperialTieFighter : public BaseEnemyShip
{
public:
    ImperialTieFighter(std::shared_ptr<PlayerSpaceShip> playerShip);
    ~ImperialTieFighter();

	void Update(GLfloat deltaTime);

	void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

protected:

private:
	Logger log;

};

#endif // ImperialTieFighter_h__