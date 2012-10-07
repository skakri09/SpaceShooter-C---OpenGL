#include "BaseEnemyShip.h"

BaseEnemyShip::BaseEnemyShip(PlayerSpaceShip* playerShip, 
	std::shared_ptr<AiState> startupState,
	std::shared_ptr<AiState> constantState)
	:log("SimpleEnemyShip", WARN),
	aiStateMachine(this, 
					startupState,
					constantState)
{
	this->playerShip = playerShip;
}

BaseEnemyShip::~BaseEnemyShip()
{
}

void BaseEnemyShip::Draw()
{

}

void BaseEnemyShip::Update( GLfloat deltaTime )
{
	SpaceShip::Update(deltaTime);
	aiStateMachine.Update(deltaTime);
}

void BaseEnemyShip::InitSpaceship( float startX, float startY, float startZ )
{
	SpaceShip::InitSpaceship(startX, startY, startZ);
}

void BaseEnemyShip::Shoot()
{

}

void BaseEnemyShip::CreateDrawable()
{

}

//void BaseEnemyShip::SetAI( EnemyAiType aiType )
//{
//	switch(aiType)
//	{
//	case SIMPLE_AI:
//		shipAI = std::make_shared<SimpleEnemyAI>();
//		break;
//	}
//}
//
