#include "ApproachXYZPlayerState.h"

void ApproachXYZPlayerState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachXYZPlayerState" << std::endl;
}

void ApproachXYZPlayerState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	targetPosition = *owner->getPlayerShip()->getPosition() - *owner->getPosition();
	targetDirection = targetPosition;
	targetDirection.Normalize();

	Vector3D velocity = targetDirection * owner->GetShipSpeed();

	owner->setVelocity(velocity);
}

void ApproachXYZPlayerState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachXYZPlayerState" << std::endl;
	owner->SetVelocity(0,0,0);
}
