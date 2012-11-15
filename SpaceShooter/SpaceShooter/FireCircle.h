/********************************************************************
    created:    15:11:2012   21:25
    filename:   FireCircle.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef FireCircle_h__
#define FireCircle_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "StarDestroyerBossFight.h"

class FireCircle : public AiState
{
public:
    FireCircle();

	virtual void Enter(BaseEnemyShip* owner);

	virtual void UpdateState(BaseEnemyShip* owner, float delta);

	virtual void Exit(BaseEnemyShip* owner);

private:
	Logger log;

	Vector3D fireDirectionVec;

	Transformable trans;
};

#endif // FireCircle_h__