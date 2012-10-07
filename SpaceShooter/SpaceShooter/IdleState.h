/********************************************************************
    created:    7:10:2012   20:26
    filename:   IdleState.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef IdleState_h__
#define IdleState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"

class IdleState : public AiState
{
public:
    IdleState():log("IdleState", INFO), AiState("IdleState"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void Execute(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;
};

#endif // IdleState_h__