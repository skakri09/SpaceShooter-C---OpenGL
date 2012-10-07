/********************************************************************
    created:    7:10:2012   16:04
    filename:   EnemySpaceshipConstantState.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef EnemySpaceshipConstantState_h__
#define EnemySpaceshipConstantState_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "Logger.h"

class EnemySpaceshipConstantState : public AiState
{
public:
    EnemySpaceshipConstantState():log("ConstAiState", INFO), 
		AiState("EnemySpaceshipConstantState"){}

	virtual void Enter(BaseEnemyShip* owner);

	virtual void Execute(BaseEnemyShip* owner, float deltaTime);

	virtual void Exit(BaseEnemyShip* owner);
private:
	Logger log;

};

#endif // EnemySpaceshipConstantState_h__