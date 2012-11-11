/********************************************************************
    created:    7:10:2012   9:08
    filename:   SimpleEnemyShip.h
    author:     Kristian Skarseth
    
    purpose:    The base for all enemy ships. It also inherits from 
				the spaceship class
*********************************************************************/
#ifndef SimpleEnemyShip_h__
#define SimpleEnemyShip_h__
#include <memory>
using std::shared_ptr;

#include "SpaceShip.h"
#include "PlayerSpaceShip.h"
#include "AiStateMachine.h"
#include "EnemySpaceshipConstantState.h"
#include "EnemyTypes.h"

class BaseEnemyShip : public SpaceShip
{
public:
    BaseEnemyShip(std::shared_ptr<PlayerSpaceShip>, 
				   std::shared_ptr<AiState> startupState,
				   std::shared_ptr<AiState> constantState,
				   int enemyHP, EnemyTypes enemyType);

    virtual ~BaseEnemyShip();
	
	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	//Initializes the spaceship. Must be called before starting to draw and update
	virtual void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ) = 0;

	std::shared_ptr<PlayerSpaceShip> getPlayerShip(){return playerShip;}

	AiStateMachine& GetAiStateMachine(){return aiStateMachine;}

	EnemyTypes GetEnemyType(){return enemyType;}

	bool WasKilledByPlayer(){return killedByPlayer;}

protected:
	//The AI state machine
	AiStateMachine aiStateMachine;

	//A pointer to the player spaceship. 
	std::shared_ptr<PlayerSpaceShip> playerShip;

	bool killedByPlayer;

private:
	Logger log;

	EnemyTypes enemyType;

};
#endif // SimpleEnemyShip_h__