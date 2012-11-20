/********************************************************************
    created:    10:11:2012   23:24
    filename:   ScoreManager.h
    author:     Kristian Skarseth
    
    purpose:    Handles the score of the player
*********************************************************************/
#ifndef ScoreManager_h__
#define ScoreManager_h__

#include "ManagerInterface.h"
#include "EnemyTypes.h"

class ScoreManager : public ManagerInterface
{
public:
	ScoreManager();
	~ScoreManager();

	void Update(float deltaTime);

	void ResetScore();

	void EnemyKilled(EnemyTypes enemyType);

	unsigned int GetScore();
private:
	unsigned int currentScore;

};

#endif // ScoreManager_h__