#include "BaseEnemyShip.h"

#pragma warning(push)
//Disabling warning about using 'this' pointer in ctor. 
#pragma warning(disable: 4355)
BaseEnemyShip::BaseEnemyShip(std::shared_ptr<PlayerSpaceShip> playerShip, 
	std::shared_ptr<AiState> startupState,
	std::shared_ptr<AiState> constantState,
	int enemyHP, EnemyTypes enemyType)
	:log("SimpleEnemyShip", WARN),
	aiStateMachine(this, 
					startupState,
					constantState),
	SpaceShip(enemyHP)
{
	this->enemyType = enemyType;

	this->playerShip = playerShip;
	
	killedByPlayer = false;
}
#pragma warning(pop)


BaseEnemyShip::~BaseEnemyShip()
{
}

void BaseEnemyShip::Draw()
{
	glPushMatrix();

	transformable.ApplyGLTransformations();
	vboDrawable.Draw();

	glPopMatrix();
}

void BaseEnemyShip::Update( GLfloat deltaTime )
{
	aiStateMachine.Update(deltaTime);
	SpaceShip::Update(deltaTime);
	if(SpaceShipCurrentHealth <= 0)
	{
		killedByPlayer = true;
	}
}
