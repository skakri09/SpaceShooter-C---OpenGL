#include "FireState.h"

void FireState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entered FireState" << std::endl;
}

void FireState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	owner->Shoot();
	//log << INFO << "" << std::endl;
}

void FireState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting Firestate" << std::endl;
}
