#include "ApproachXYZPlayerState.h"

void ApproachXYZPlayerState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachXYZPlayerState" << std::endl;
}

void ApproachXYZPlayerState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	targetPosition = *owner->getPlayerShip()->transformable.getPosition() - *owner->transformable.getPosition();
	targetDirection = targetPosition;
	targetDirection.Normalize();

	Vector3D velocity = targetDirection * owner->GetShipSpeed();

	owner->transformable.setVelocity(velocity);
}

void ApproachXYZPlayerState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachXYZPlayerState" << std::endl;
	owner->transformable.SetVelocity(0,0,0);
}
