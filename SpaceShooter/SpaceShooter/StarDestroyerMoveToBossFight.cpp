#include "StarDestroyerMoveToBossFight.h"

void StarDestroyerMoveToBossFight::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering StarDestroyerMoveToBossFight" << std::endl;
}

void StarDestroyerMoveToBossFight::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	log << INFO << "--" << std::endl;
}

void StarDestroyerMoveToBossFight::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting StarDestroyerMoveToBossFight" << std::endl;
}
