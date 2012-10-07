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

class FollowPlayerState : public AiState
{
public:
    FollowPlayerState():log("FollowPlayerState", INFO), AiState("FollowPlayerState"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void Execute(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;
};

#endif // FollowPlayerState_h__