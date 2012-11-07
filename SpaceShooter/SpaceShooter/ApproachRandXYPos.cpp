#include "ApproachRandXYPos.h"


void ApproachRandXYPos::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachRandXYPos state" << std::endl;
	targetPosition.setX(GetRandFloat(FRUSTUM_LEFT, FRUSTUM_RIGHT));
	targetPosition.setY(GetRandFloat(FRUSTUM_TOP, FRUSTUM_BOTTOM));
	targetPosition.setZ(-60);
	targetDirection = targetPosition - *owner->transformable.getPosition();
	targetDirection.Normalize();
	velocity = targetDirection * 200;
	owner->transformable.SetVelocity(velocity);
}

void ApproachRandXYPos::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	float dist = owner->transformable.getPosition()->Distance(targetPosition);
	if(dist <= 40)
	{
		Vector3D newVel = velocity;
		newVel*= (dist/40);
		owner->transformable.SetVelocity(newVel);
		if(dist <= 1)
		{
			owner->GetAiStateMachine().ChangeState(std::make_shared<FireState>());
		}
		
	}
}

void ApproachRandXYPos::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachXYZPlayerState" << std::endl;
	owner->transformable.SetVelocity(0,0,0);
}
