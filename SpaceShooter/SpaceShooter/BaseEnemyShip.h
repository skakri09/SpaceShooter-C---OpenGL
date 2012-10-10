/********************************************************************
    created:    7:10:2012   9:08
    filename:   SimpleEnemyShip.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SimpleEnemyShip_h__
#define SimpleEnemyShip_h__
#include <memory>
using std::shared_ptr;

#include "SpaceShip.h"
#include "PlayerSpaceShip.h"
#include "AiStateMachine.h"
#include "EnemySpaceshipConstantState.h"
//CD on the spaceships fireing of projectiles in seconds
static const float FIRE_COOLDOWN_SIMPLE_ENEMY  = 0.2f;

//The speed of a square bullet for the player
static const float SQUARE_BULLET_SPEED_SIMPLE_ENEMY = 100.0f;

enum EnemyAiType{SIMPLE_AI};

class BaseEnemyShip : public SpaceShip
{
public:
    BaseEnemyShip(PlayerSpaceShip* playerShip, 
				   std::shared_ptr<AiState> startupState,
				   std::shared_ptr<AiState> constantState);

    virtual ~BaseEnemyShip();

	//Does drawing of the spaceship.
	virtual void Draw();

	//Draws the spaceship and takes care of the bullets it owns
	virtual void Update(GLfloat deltaTime);

	//virtual void InitSpaceship(float startX, float startY, float startZ,
	//							float scaleX, float scaleY, float scaleZ);
	
	//Shoots the gun, calling the fire function from spaceShipbase 
	//with proper parameters (the cd and speed defined in top of class)
	virtual void Shoot();

	PlayerSpaceShip* getPlayerShip(){return playerShip;}

	//void SetAI(EnemyAiType aiType);

	int getSpaceShipHp(){return spaceShipHP;}

	void setActive(bool isActive){this->isActive = isActive;}

protected:
	//The AI state machine
	AiStateMachine aiStateMachine;

	//A pointer to the player spaceship. 
	PlayerSpaceShip* playerShip;

	//Creates the displaylist/vbo for the spaceship
	virtual void CreateDrawable();

	//Takes care of switching between AI states. Any enemy spaceship
	//need to implement their own functionality in this function
	virtual void HandleAI() = 0;
	
	int spaceShipHP;

	bool isActive;
	
private:
	Logger log;



};
#endif // SimpleEnemyShip_h__