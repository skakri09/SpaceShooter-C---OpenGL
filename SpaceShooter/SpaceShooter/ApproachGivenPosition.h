/********************************************************************
    created:    13:11:2012   10:15
    filename:   ApproachGivenPosition.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ApproachGivenPosition_h__
#define ApproachGivenPosition_h__

#include "AiState.h"
#include "BaseEnemyShip.h"
#include "logger.h"
#include "GetRandomFloat.h"

class ApproachGivenPosition : public AiState
{
public:
	ApproachGivenPosition(float xPos, float yPos, float zPos, float velocity);

	virtual void Enter(BaseEnemyShip* owner);

	virtual void UpdateState(BaseEnemyShip* owner, float delta);

	virtual void Exit(BaseEnemyShip* owner);

private:
	Logger log;
	Vector3D targetPos;
	Vector3D velocity;
	float velValue;
	bool destReached;

	std::shared_ptr<AiState> stateToEnterOnceReached;
};

#endif // ApproachGivenPosition_h__