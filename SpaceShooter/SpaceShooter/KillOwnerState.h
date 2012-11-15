/********************************************************************
    created:    15:11:2012   13:42
    filename:   KillOwnerState.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef KillOwnerState_h__
#define KillOwnerState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"

class KillOwnerState : public AiState
{
public:
    KillOwnerState():log("KillOwnerState", INFO),AiState("KillOwnerState"){}

	virtual void Enter(BaseEnemyShip* enemy)
	{
		enemy->FlagForKill();
	}

	virtual void UpdateState(BaseEnemyShip* enemy, float delta){}

	virtual void Exit(BaseEnemyShip* enemy){}

private:
	Logger log;
};

#endif // KillOwnerState_h__