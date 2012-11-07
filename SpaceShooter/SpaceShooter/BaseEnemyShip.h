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

class BaseEnemyShip : public SpaceShip
{
public:
    BaseEnemyShip(PlayerSpaceShip* playerShip, 
				   std::shared_ptr<AiState> startupState,
				   std::shared_ptr<AiState> constantState,
				   int enemyHP);

    virtual ~BaseEnemyShip();
	
	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	//Initializes the spaceship. Must be called before starting to draw and update
	virtual void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ) = 0;

	PlayerSpaceShip* getPlayerShip(){return playerShip;}

	AiStateMachine& GetAiStateMachine(){return aiStateMachine;}

protected:
	//The AI state machine
	AiStateMachine aiStateMachine;

	//A pointer to the player spaceship. 
	PlayerSpaceShip* playerShip;

	bool isActive;

private:
	Logger log;



};
#endif // SimpleEnemyShip_h__