/********************************************************************
    created:    24:10:2012   13:18
    filename:   StarDestroyerShipSpawning.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef StarDestroyerShipSpawning_h__
#define StarDestroyerShipSpawning_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"

class StarDestroyerShipSpawning : public AiState
{
public:
	StarDestroyerShipSpawning():log("StarDestroyerShipSpawning", WARN),AiState("StarDestroyerShipSpawning"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;
};

#endif // StarDestroyerShipSpawning_h__