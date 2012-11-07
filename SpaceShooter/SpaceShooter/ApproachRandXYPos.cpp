#include "ApproachRandXYPos.h"


void ApproachRandXYPos::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachRandXYPos state" << std::endl;
	targetPosition.setX(GetRandFloat(FRUSTUM_LEFT, FRUSTUM_RIGHT));
	targetPosition.setY(GetRandFloat(FRUSTUM_TOP, FRUSTUM_BOTTOM));
	targetPosition.setZ(-60);
	targetDirection = targetPosition - *owner->transformable.getPosition();
	targetDirection.Normalize();
	Vector3D velocity = targetDirection * owner->GetShipSpeed();
	owner->transformable.SetVelocity(velocity);
}

void ApproachRandXYPos::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	float dist = owner->transformable.getPosition()->Distance(targetPosition);
	if(dist <= 10)
	{
		owner->GetAiStateMachine().ChangeState(std::make_shared<FireState>());
		//owner->transformable.SetVelocity(0, 0, 0);
		//owner->transformable.SetZPos(-60);
	}
}

void ApproachRandXYPos::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachXYZPlayerState" << std::endl;
	owner->transformable.SetVelocity(0,0,0);
}
