#include "StarDestroyerBossFight.h"

void StarDestroyerBossFight::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering StarDestroyerBossFight" << std::endl;
}

void StarDestroyerBossFight::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	log << INFO << "--" << std::endl;
}

void StarDestroyerBossFight::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting StarDestroyerBossFight" << std::endl;
}
