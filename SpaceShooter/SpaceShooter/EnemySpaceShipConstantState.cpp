#include "EnemySpaceShipConstantState.h"


void EnemySpaceshipConstantState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "This enemy just became active" << std::endl;
}

void EnemySpaceshipConstantState::Execute( BaseEnemyShip* owner, float deltaTime )
{
	if(owner->getSpaceShipHp() <= 0)
	{
		owner->setActive(false);
		log << INFO << "This enemy ran out of HP" << std::endl;
	}
}

void EnemySpaceshipConstantState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "This enemy has died" << std::endl;
}
