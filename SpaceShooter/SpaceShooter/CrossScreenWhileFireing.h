/********************************************************************
    created:    7:11:2012   13:38
    filename:   CrossScreenWhileFireing.h
    author:     Kristian Skarseth
    
    purpose:    Moves from one side to the opposite side of the frustum
*********************************************************************/
#ifndef CrossScreenWhileFireing_h__
#define CrossScreenWhileFireing_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "GameConstants.h"
class CrossScreenWhileFireing : public AiState
{
public:
    CrossScreenWhileFireing():log("CrossScreenWhileFireing", INFO),AiState("CrossScreenWhileFireing"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;
	Vector3D targetVelocity;
	Vector3D targetPos;
};

#endif // CrossScreenWhileFireing_h__