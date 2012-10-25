#include "StarDestroyerShipSpawning.h"

void StarDestroyerShipSpawning::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering StarDestroyerShipSpawning" << std::endl;
}

void StarDestroyerShipSpawning::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	log << INFO << "--" << std::endl;
}

void StarDestroyerShipSpawning::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting StarDestroyerShipSpawning" << std::endl;
}
