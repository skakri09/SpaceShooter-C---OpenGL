#include "FollowPlayerState.h"

void FollowPlayerState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering followPlayerState" << std::endl;
	//targetPosition = *owner->getPlayerShip()->getPosition() - *owner->getPosition();
	//targetDirection = targetPosition;
	//targetDirection.setZ(0);
	//targetDirection.Normalize();
}

void FollowPlayerState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	targetPosition = *owner->getPlayerShip()->getPosition() - *owner->getPosition();
	targetDirection = targetPosition;
	targetDirection.setZ(0);
	targetDirection.Normalize();

	Vector3D velocity = targetDirection * SIMPLE_ENEMY_SPEED;

	owner->setVelocity(velocity);
	//log << INFO <<"  " << owner->getXPos()<<"  " << owner->getZPos()<<"  " << owner->getZPos() << std::endl;
}

void FollowPlayerState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "--" << std::endl;
}
