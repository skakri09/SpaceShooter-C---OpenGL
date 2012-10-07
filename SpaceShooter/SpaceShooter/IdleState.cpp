#include "IdleState.h"

void IdleState::Enter( BaseEnemyShip* owner )
{
	owner->SetVelocity(0.0f, 0.0f, 0.0f);
	log << INFO << "Entering Idle state" << std::endl;
}

void IdleState::Execute( BaseEnemyShip* owner, float deltaTime )
{
	//log << INFO << "--" << std::endl;
}

void IdleState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting Idle State" << std::endl;
}
