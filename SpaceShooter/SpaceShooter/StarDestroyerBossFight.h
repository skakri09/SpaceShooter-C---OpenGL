/********************************************************************
    created:    15:11:2012   13:30
    filename:   StarDestroyerBossFight.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef StarDestroyerBossFight_h__
#define StarDestroyerBossFight_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "FireCircle.h"

class StarDestroyerBossFight : public AiState
{
public:
    StarDestroyerBossFight():log("StarDestroyerBossFight", WARN),AiState("StarDestroyerBossFight"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;

	int shotsFired;
};

#endif // StarDestroyerBossFight_h__