/********************************************************************
    created:    12:10:2012   18:29
    filename:   ApproachXYPlayerState.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ApproachXYPlayerState_h__
#define ApproachXYPlayerState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"

class ApproachXYPlayerState : public AiState
{
public:
    ApproachXYPlayerState():log("ApproachPlayerState", INFO),AiState("ApproachXYPlayerState"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Vector3D targetPosition;
	Vector3D targetDirection;

	Logger log;
};

#endif // ApproachXYPlayerState_h__