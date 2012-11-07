#include "EnemySpaceShipConstantState.h"


void EnemySpaceshipConstantState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "This enemy just became active" << std::endl;
}

void EnemySpaceshipConstantState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	Vector3D* position = owner->transformable.getPosition();
	//Killing all enemies in front or far behind frustum
	if(position->getZ() >= 15 || position->getZ() < -15000)
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
