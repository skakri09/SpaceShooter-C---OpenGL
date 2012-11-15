#include "ApproachGivenPosition.h"

ApproachGivenPosition::ApproachGivenPosition( float xPos, float yPos, 
		float zPos, float velocity)
	:log("ApproachGivenPosition", INFO),
	AiState("ApproachGivenPosition")

{
	targetPos.setValues(xPos, yPos, zPos);
	velValue = velocity;
	this->stateToEnterOnceReached = stateToEnterOnceReached;
}

void ApproachGivenPosition::Enter( BaseEnemyShip* owner )
{
	velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity *= velValue;
	owner->transformable.SetVelocity(velocity);
	destReached = false;
}

void ApproachGivenPosition::UpdateState( BaseEnemyShip* owner, float delta )
{
	if(!destReached)
	{
		//Gradually decrementing the velocity of the owner ship when we are getting close to the destination
		float dist = owner->transformable.getPosition()->Distance(targetPos);
		if(dist <= 60)
		{
			Vector3D newVel = velocity;
			newVel*= (dist/60);
			owner->transformable.SetVelocity(newVel);
			if(dist <= 1)
			{
				destReached = true;
			}

		}
	}
	
}

void ApproachGivenPosition::Exit( BaseEnemyShip* owner )
{
	owner->transformable.SetVelocity(0, 0, 0);
}
