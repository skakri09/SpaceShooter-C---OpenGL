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
#include "SpaceShipManager.h"
#include "ImperialTieFighter.h"
#include "ImperialTieInterceptor.h"
#include "GetRandomFloat.h"

class StarDestroyerShipSpawning : public AiState
{
public:
	StarDestroyerShipSpawning();

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;
	BaseEnemyShip* ownerShip;
	enum Direction{LEFT, RIGHT, UP, DOWN};
	Direction direction;

	void UpdateDirection(BaseEnemyShip* owner);
	void HandleShipSpawning(float deltaTime);
	float lastImpInterceptorSpawn;
	float lastImpTieFighterSpawn;
};

#endif // StarDestroyerShipSpawning_h__