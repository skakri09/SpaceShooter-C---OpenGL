#include "StarDestroyerBossFight.h"

void StarDestroyerBossFight::Enter( BaseEnemyShip* owner )
{
	log << WARN << "Entering StarDestroyerBossFight" << std::endl;
}

void StarDestroyerBossFight::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
}

void StarDestroyerBossFight::Exit( BaseEnemyShip* owner )
{
	log << WARN << "Exiting StarDestroyerBossFight" << std::endl;
}
