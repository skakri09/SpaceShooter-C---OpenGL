/********************************************************************
	created:	6:11:2012   13:50
	filename: 	ApproachRandXYPos.h
	author:		Kristian Skarseth
	
	purpose:	The state finds a random position on the XY plane in front of the
				player, and approaches it. Switches into FireState once the 
				destination is reached.
*********************************************************************/
#ifndef ApproachRandXYPos_h__
#define ApproachRandXYPos_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "GetRandomFloat.h"
#include "GameConstants.h"
#include "FireState.h"

class ApproachRandXYPos : public AiState
{
public:
	ApproachRandXYPos():log("ApproachRandXYPos", WARN),AiState("ApproachRandXYPos"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;

	Vector3D targetPosition;
	Vector3D targetDirection;
	Vector3D velocity;

	bool destReached;
};

#endif // ApproachRandXYPos_h__
