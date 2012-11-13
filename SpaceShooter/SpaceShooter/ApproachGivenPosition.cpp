#include "ApproachGivenPosition.h"

ApproachGivenPosition::ApproachGivenPosition( float xPos, float yPos, float zPos, float velocity )
	:log("ApproachGivenPosition", INFO),
	AiState("ApproachGivenPosition")

{
	targetPos.setValues(xPos, yPos, zPos);
	velValue = velocity;
}

void ApproachGivenPosition::Enter( BaseEnemyShip* owner )
{
	velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity *= velocity;
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
				//enter bossfight state
				//owner->GetAiStateMachine().ChangeState(std::make_shared<FireState>());
				destReached = true;
			}

		}
	}
	
}

void ApproachGivenPosition::Exit( BaseEnemyShip* owner )
{

}
