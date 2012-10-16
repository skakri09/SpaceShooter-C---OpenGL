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
//CD on the spaceships fireing of projectiles in seconds
static const float FIRE_COOLDOWN_SIMPLE_ENEMY  = 0.2f;

//The speed of a square bullet for the player
static const float SQUARE_BULLET_SPEED_SIMPLE_ENEMY = 50.0f;

enum EnemyAiType{SIMPLE_AI};

class BaseEnemyShip : public SpaceShip
{
public:
    BaseEnemyShip(PlayerSpaceShip* playerShip, 
				   std::shared_ptr<AiState> startupState,
				   std::shared_ptr<AiState> constantState,
				   int enemyHP);

    virtual ~BaseEnemyShip();
	
	virtual void InitSpaceship(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

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

	float GetShipSpeed(){return ShipSpeed;}
protected:
	//The AI state machine
	AiStateMachine aiStateMachine;

	//A pointer to the player spaceship. 
	PlayerSpaceShip* playerShip;

	//Creates the displaylist/vbo for the spaceship
	virtual void CreateGameObject();

	//Takes care of switching between AI states. Any enemy spaceship
	//need to implement their own functionality in this function
	virtual void HandleAI() = 0;
	
	int spaceShipHP;

	bool isActive;
	
	float ShipSpeed;
private:
	Logger log;



};
#endif // SimpleEnemyShip_h__