/********************************************************************
    created:    7:10:2012   17:14
    filename:   FireState.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef FireState_h__
#define FireState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "Logger.h"

class FireState : public AiState
{
public:
    FireState():log("FireState", WARN), AiState("FireState"){}

	virtual void Enter(BaseEnemyShip* owner);

	virtual void UpdateState(BaseEnemyShip* owner, float deltaTime);

	virtual void Exit(BaseEnemyShip* owner);

private:
	Logger log;
};

#endif // FireState_h__