/********************************************************************
    created:    7:10:2012   16:04
    filename:   EnemySpaceshipConstantState.h
    author:     Kristian Skarseth
    
    purpose:    The constant state for an enemy spaceship. It takes care
				of destorying enemy ships that may have bugged and are way
				outside the frustum. 
*********************************************************************/
#ifndef EnemySpaceshipConstantState_h__
#define EnemySpaceshipConstantState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "Logger.h"

class EnemySpaceshipConstantState : public AiState
{
public:
    EnemySpaceshipConstantState():log("ConstAiState", WARN), 
		AiState("EnemySpaceshipConstantState"){}

	virtual void Enter(BaseEnemyShip* owner);

	virtual void UpdateState(BaseEnemyShip* owner, float deltaTime);

	virtual void Exit(BaseEnemyShip* owner);

private:
	Logger log;

};

#endif // EnemySpaceshipConstantState_h__