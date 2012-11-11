#include "ScoreManager.h"


ScoreManager::ScoreManager()
{
	currentScore = 0;
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::ResetScore()
{
	currentScore = 0;
}

unsigned int ScoreManager::GetScore()
{
	return currentScore;
}

void ScoreManager::Update( float deltaTime )
{

}

void ScoreManager::EnemyKilled( EnemyTypes enemyType )
{
	switch(enemyType)
	{
	case IMPERIAL_STAR_DESTROYER:
		currentScore += 1000;
		break;
	case IMPERIAL_TIE_FIGHTER:
		currentScore += 50;
		break;
	case IMPERIAL_TIE_INTERCEPTOR:
		currentScore += 100;
		break;
	}
}
