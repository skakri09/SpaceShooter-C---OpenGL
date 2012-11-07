/********************************************************************
	created:	6:11:2012   15:38
	filename: 	ApproachEdge.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef ApproachEdge_h__
#define ApproachEdge_h__

#include "Logger.h"
#include "AiState.h"
#include "BaseEnemyShip.h"

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
};

#endif // ApproachEdge_h__
