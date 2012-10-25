#include "ApproachXYPlayerState.h"

void ApproachXYPlayerState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachXYZPlayerState" << std::endl;
}

void ApproachXYPlayerState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	targetPosition = *owner->getPlayerShip()->getPosition() - *owner->getPosition();
	targetDirection = targetPosition;
	targetDirection.setZ(0);
	targetDirection.Normalize();
	Vector3D velocity = targetDirection * owner->GetShipSpeed();

	owner->setVelocity(velocity);
}

void ApproachXYPlayerState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachXYZPlayerState" << std::endl;
	owner->SetVelocity(0,0,0);
}
