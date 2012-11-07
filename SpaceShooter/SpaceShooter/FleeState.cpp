#include "FleeState.h"

void FleeState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering FleeState" << std::endl;
	SetTargetPos(owner->transformable.getPosition());
	Vector3D velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity = velocity * 50;
	owner->transformable.SetVelocity(velocity);
}

void FleeState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	Vector3D velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity = velocity * 50;
	owner->transformable.SetVelocity(velocity);

	float dist = owner->transformable.getPosition()->Distance(targetPos);
	if(dist <= 3)
	{
		owner->FlagForKill();
	}

}

void FleeState::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting FleeState" << std::endl;
}


void FleeState::SetTargetPos( Vector3D* currentPos )
{
	float xPos = currentPos->getX();
	float yPos = currentPos->getY();
	
	targetPos.setZ(-40);
	float plusVal = abs(targetPos.getZ()*2);
	if(xPos > 0)
	{
		if (yPos > 0)
		{
			if(xPos > yPos)
			{
				//right
				targetPos.setX(FRUSTUM_RIGHT + plusVal);
				targetPos.setY(currentPos->getY());
			}
			else
			{
				//up
				targetPos.setY(FRUSTUM_TOP + plusVal);
				targetPos.setX(currentPos->getX());
			}
		}
		else
		{
			if(xPos > abs(yPos))
			{
				//right
				targetPos.setX(FRUSTUM_RIGHT + plusVal);
				targetPos.setY(currentPos->getY());
			}
			else
			{
				//down
				targetPos.setY(FRUSTUM_BOTTOM - plusVal);
				targetPos.setX(currentPos->getX());
			}
		}
	}
	else
	{
		if(yPos > 0)
		{
			if(abs(xPos > yPos))
			{
				//left
				targetPos.setX(FRUSTUM_LEFT - plusVal);
				targetPos.setY(currentPos->getY());
			}
			else
			{
				//up
				targetPos.setY(FRUSTUM_TOP + plusVal);
				targetPos.setX(currentPos->getX());
			}
		}
		else
		{
			if(abs(xPos) > abs(yPos))
			{
				//left
				targetPos.setX(FRUSTUM_LEFT - plusVal);
				targetPos.setY(currentPos->getY());
			}
			else
			{
				//down
				targetPos.setY(FRUSTUM_BOTTOM - plusVal);
				targetPos.setX(currentPos->getX());
			}
		}
	}
}
