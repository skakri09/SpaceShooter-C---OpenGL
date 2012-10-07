#include "FollowPlayerState.h"

void FollowPlayerState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering followPlayerState" << std::endl;
}

void FollowPlayerState::Execute( BaseEnemyShip* owner, float deltaTime )
{
	Vector3D newVel = *owner->getPlayerShip()->getVelocity();
	newVel.setZ(0.0);
	owner->setVelocity(newVel);
	log << INFO << "--" << std::endl;
}

void FollowPlayerState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "--" << std::endl;
}
