#include "CrossScreenWhileFireing.h"

void CrossScreenWhileFireing::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering CrossScreenWhileFireing" << std::endl;
	targetPos.setY(owner->transformable.getYPos());
	targetPos.setZ(owner->transformable.getZPos());
	
	if(owner->transformable.getXPos() >= 0)
	{
		targetPos.setX(FRUSTUM_LEFT-90);
	}
	else
	{
		targetPos.setX(FRUSTUM_RIGHT+90);
	}
	targetVelocity = targetPos - *owner->transformable.getPosition();
	targetVelocity.Normalize();
	targetVelocity = targetVelocity * 30;
	owner->transformable.setYVel(targetVelocity.getY());
	owner->transformable.setZVel(targetVelocity.getZ());
}

void CrossScreenWhileFireing::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	
	if( (targetVelocity.getX() < 0 && owner->transformable.getXVel() > targetVelocity.getX()) 
		|| (targetVelocity.getX() > 0 && owner->transformable.getXVel() < targetVelocity.getX()))
	{
		log << INFO << "targetX: " << targetVelocity.getX() << " curr:" << owner->transformable.getXVel() << std::endl;
		log << INFO << "targetY: " << targetVelocity.getY() << " curr:" << owner->transformable.getYVel() << std::endl;
		log << INFO << "targetZ: " << targetVelocity.getZ() << " curr:" << owner->transformable.getZVel() << std::endl;
		Vector3D velAddition = targetVelocity*deltaTime;
		Vector3D newVel = *owner->transformable.getVelocity() + velAddition;
		owner->transformable.SetVelocity(newVel);
	}
	owner->Shoot(LASER_SLOW);

	float dist = owner->transformable.getPosition()->Distance(targetPos);
	if(dist <= 3)
	{
		owner->FlagForKill();
	}
}

void CrossScreenWhileFireing::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting CrossScreenWhileFireing" << std::endl;
}
