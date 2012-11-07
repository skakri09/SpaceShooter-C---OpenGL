#include "ApproachXYZPlayerState.h"

void ApproachXYZPlayerState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachXYZPlayerState" << std::endl;
}

void ApproachXYZPlayerState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	//gets the position of the player, and sets a new velocity of the owner in order to move towards the player
	targetPosition = *owner->getPlayerShip()->transformable.getPosition() - *owner->transformable.getPosition();
	targetDirection = targetPosition;
	targetDirection.Normalize();

	Vector3D velocity = targetDirection * 120;

	owner->transformable.SetVelocity(velocity);
}

void ApproachXYZPlayerState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachXYZPlayerState" << std::endl;
	owner->transformable.SetVelocity(0,0,0);
}
