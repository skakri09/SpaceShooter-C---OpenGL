/********************************************************************
    created:    7:11:2012   11:38
    filename:   FleeState.h
    author:     Kristian Skarseth
    
    purpose:    Finds a destination outside the frustum and moves there. Tells
				the owner ship it can destruct once it the destination is reached
*********************************************************************/
#ifndef FleeState_h__
#define FleeState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "GameConstants.h"

class FleeState : public AiState
{
public:
    FleeState():log("FleeState", INFO),AiState("FleeState"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;

	Vector3D targetPos;

	//Decides the target position based on the start position of the owner spaceship
	//Function will try to find the shortest way out from the frustum
	void SetTargetPos(Vector3D* currentPos);
};

#endif // FleeState_h__