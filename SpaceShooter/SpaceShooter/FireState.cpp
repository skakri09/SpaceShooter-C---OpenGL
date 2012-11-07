#include "FireState.h"

void FireState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entered FireState" << std::endl;
	shotsFired = 0;
	owner->transformable.SetVelocity(0, 0, 0);
}

void FireState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	if(owner->getPlayerShip()->IsAlive())
	{
		if(owner->Shoot(LASER_SLOW))
		{
			shotsFired++;
			log << WARN << shotsFired << std::endl;
		}
		if(shotsFired >= 4)
		{
			owner->GetAiStateMachine().ChangeState(std::make_shared<FleeState>());
		}
	}
	
}

void FireState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting Firestate" << std::endl;
}
