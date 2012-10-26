#include "ApproachXYPlayerState.h"

void ApproachXYPlayerState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachXYZPlayerState" << std::endl;
}

void ApproachXYPlayerState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	targetPosition = *owner->getPlayerShip()->transformable.getPosition() - *owner->transformable.getPosition();
	targetDirection = targetPosition;
	targetDirection.setZ(0);
	targetDirection.Normalize();
	Vector3D velocity = targetDirection * owner->GetShipSpeed();

	owner->transformable.setVelocity(velocity);
}

void ApproachXYPlayerState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachXYZPlayerState" << std::endl;
	owner->transformable.SetVelocity(0,0,0);
}
