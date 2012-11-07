/********************************************************************
    created:    12:10:2012   18:29
    filename:   ApproachXYZPlayerState.h
    author:     Kristian Skarseth
    
    purpose:    A simple state for approaching the player in the XYZ plane
*********************************************************************/
#ifndef ApproachXYZPlayerState_h__
#define ApproachXYZPlayerState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"

class ApproachXYZPlayerState : public AiState
{
public:
    ApproachXYZPlayerState():log("ApproachPlayerState", WARN),AiState("ApproachXYZPlayerState"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Vector3D targetPosition;
	Vector3D targetDirection;
	Logger log;
};

#endif // ApproachXYZPlayerState_h__