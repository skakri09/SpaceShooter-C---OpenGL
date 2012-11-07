#include "ApproachEdge.h"


void ApproachEdge::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachEdge state" << std::endl;
	SetDestination(owner->transformable.getPosition());
	velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity*= 200;
	owner->transformable.SetVelocity(velocity);
}

void ApproachEdge::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	float dist = owner->transformable.getPosition()->Distance(targetPos);
	if(dist <= 40)
	{
		Vector3D newVel = velocity;
		newVel*= (dist/40);
		owner->transformable.SetVelocity(newVel);
		if(dist <= 1)
		{
			owner->GetAiStateMachine().ChangeState(std::make_shared<CrossScreenWhileFireing>());
		}

	}

}

void ApproachEdge::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachEdge state" << std::endl;
}

void ApproachEdge::SetDestination( Vector3D* currPos )
{
	if(currPos->getX() >= 0)
	{
		targetPos.setX(FRUSTUM_RIGHT+20);
	}
	else
	{
		targetPos.setX(FRUSTUM_LEFT-20);	
	}
	float boundries = abs(FRUSTUM_BOTTOM - FRUSTUM_TOP);
	boundries/=10;
	targetPos.setY(GetRandFloat( (FRUSTUM_BOTTOM+boundries), (FRUSTUM_TOP-boundries) ));
	targetPos.setZ(-60.0f);
}
