#include "EnemySpaceShipConstantState.h"


void EnemySpaceshipConstantState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "This enemy just became active" << std::endl;
}

void EnemySpaceshipConstantState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	if(owner->getSpaceShipHp() <= 0)
	{
		//log << INFO << "This enemy ran out of HP" << std::endl;
	}

	Vector3D* position = owner->transformable.getPosition();
	//Killing all enemies in front of frustum
	if(position->getZ() >= 10)
	{
		owner->FlagForKill();
	}

	//Killing enemies far outside the edges of frustum.
	if(position->getX() > 1000 || position->getX() < -1000
		|| position->getY() > 1000 || position->getY() < -1000)
	{
		owner->FlagForKill();
	}
}

void EnemySpaceshipConstantState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "This enemy has died" << std::endl;
}
