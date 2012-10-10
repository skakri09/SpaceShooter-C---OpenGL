#include "BaseEnemyShip.h"

#pragma warning(push)
//Disabling warning about using 'this' pointer in ctor. 
#pragma warning(disable: 4355)
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
#pragma warning(pop)

BaseEnemyShip::~BaseEnemyShip()
{
}

void BaseEnemyShip::Draw()
{
	SpaceShip::Draw();
}

void BaseEnemyShip::Update( GLfloat deltaTime )
{
	aiStateMachine.Update(deltaTime);
	SpaceShip::Update(deltaTime);
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
