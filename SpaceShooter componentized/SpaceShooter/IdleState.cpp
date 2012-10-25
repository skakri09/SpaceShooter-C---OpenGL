#include "IdleState.h"

void IdleState::Enter( BaseEnemyShip* owner )
{
	owner->SetVelocity(0.0f, 0.0f, 0.0f);
	log << INFO << "Entering Idle state" << std::endl;
}

void IdleState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
}

void IdleState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting Idle State" << std::endl;
}
