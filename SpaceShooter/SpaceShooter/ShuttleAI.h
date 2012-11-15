/********************************************************************
    created:    15:11:2012   15:07
    filename:   ShuttleAI.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ShuttleAI_h__
#define ShuttleAI_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"

#include "Vector3d.h"
#include "GetRandomFloat.h"
#include "GameConstants.h"

class ShuttleAI : public AiState
{
public:
    ShuttleAI();
	
	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;

	Vector3D dsStartPos; 
	Vector3D leftTargetPos; 
	Vector3D rightTargetPos;
	Vector3D planetTargetPos;

	Vector3D startVel;
	Vector3D leftToRightVel;
	Vector3D flyOutVel;
};

#endif // ShuttleAI_h__