/********************************************************************
    created:    7:10:2012   20:26
    filename:   IdleState.h
    author:     Kristian Skarseth
    
    purpose:    A idle state. Does nothing, because it can.
*********************************************************************/
#ifndef IdleState_h__
#define IdleState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"

class IdleState : public AiState
{
public:
    IdleState():log("IdleState", WARN), AiState("IdleState"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;
};

#endif // IdleState_h__