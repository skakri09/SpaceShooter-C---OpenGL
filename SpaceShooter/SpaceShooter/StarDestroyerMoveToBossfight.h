/********************************************************************
    created:    15:11:2012   20:57
    filename:   StarDestroyerMoveToBossfight.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef StarDestroyerMoveToBossfight_h__
#define StarDestroyerMoveToBossfight_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "StarDestroyerBossFight.h"

class StarDestroyerMoveToBossfight : public AiState
{
public:
    StarDestroyerMoveToBossfight():log("StarDestroyerMoveToBossfight", INFO),AiState("StarDestroyerMoveToBossfight"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

private:
	Logger log;

	Vector3D targetPos;
	Vector3D velocity;
	
	static float timer;
};

#endif // StarDestroyerMoveToBossfight_h__