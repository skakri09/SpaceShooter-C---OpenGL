/********************************************************************
    created:    7:10:2012   19:44
    filename:   FollowPlayerState.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef FollowPlayerState_h__
#define FollowPlayerState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "GameConstants.h"

class FollowPlayerState : public AiState
{
public:
    FollowPlayerState():log("FollowPlayerState", WARN), AiState("FollowPlayerState"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;

	Vector3D targetPosition;
	Vector3D targetDirection;
};

#endif // FollowPlayerState_h__