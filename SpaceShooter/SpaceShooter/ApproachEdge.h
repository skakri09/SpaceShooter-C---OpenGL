/********************************************************************
	created:	6:11:2012   15:38
	filename: 	ApproachEdge.h
	author:		Kristian Skarseth
	
	purpose:	Sets a destination along an edge of the frustum and moves
				towards it. Switches into CrossScreenWhileFireing state 
				once the destination is reached.
*********************************************************************/
#ifndef ApproachEdge_h__
#define ApproachEdge_h__

#include "Logger.h"
#include "AiState.h"
#include "BaseEnemyShip.h"
#include "GetRandomFloat.h"
#include "GameConstants.h"
#include "CrossScreenWhileFireing.h"

class ApproachEdge : public AiState
{
public:
	ApproachEdge():log("ApproachEdge", WARN),AiState("ApproachEdge"){}

	virtual void Enter(BaseEnemyShip* enemy);

	virtual void UpdateState(BaseEnemyShip* enemy, float delta);

	virtual void Exit(BaseEnemyShip* enemy);

protected:

private:
	Logger log;

	Vector3D targetPos;
	Vector3D velocity;

	void SetDestination(Vector3D* currPos);
};

#endif // ApproachEdge_h__
