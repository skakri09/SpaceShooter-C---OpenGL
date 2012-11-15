#include "FleeState.h"

void FleeState::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering FleeState" << std::endl;
	SetTargetPos(owner->transformable.getPosition());
	Vector3D velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity = velocity * 30;
	owner->transformable.SetVelocity(velocity);
}

void FleeState::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	Vector3D velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity = velocity * 30;
	owner->transformable.SetVelocity(velocity);

	SetRotation(owner, deltaTime);

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
				direction = RIGHT;
			}
			else
			{
				//up
				targetPos.setY(FRUSTUM_TOP + plusVal);
				targetPos.setX(currentPos->getX());
				direction = UP;
			}
		}
		else
		{
			if(xPos > abs(yPos))
			{
				//right
				targetPos.setX(FRUSTUM_RIGHT + plusVal);
				targetPos.setY(currentPos->getY());
				direction = RIGHT;
			}
			else
			{
				//down
				targetPos.setY(FRUSTUM_BOTTOM - plusVal);
				targetPos.setX(currentPos->getX());
				direction = DOWN;
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
				direction = LEFT;
			}
			else
			{
				//up
				targetPos.setY(FRUSTUM_TOP + plusVal);
				targetPos.setX(currentPos->getX());
				direction = UP;
			}
		}
		else
		{
			if(abs(xPos) > abs(yPos))
			{
				//left
				targetPos.setX(FRUSTUM_LEFT - plusVal);
				targetPos.setY(currentPos->getY());
				direction = LEFT;
			}
			else
			{
				//down
				targetPos.setY(FRUSTUM_BOTTOM - plusVal);
				targetPos.setX(currentPos->getX());
				direction = DOWN;
			}
		}
	}
}

void FleeState::SetRotation( BaseEnemyShip* owner, float deltaTime )
{
	float rotationSpeed = 90.0f;

	switch(direction)
	{
	case RIGHT:
		if(owner->transformable.GetYRot() < 90.0f)
		{
			owner->transformable.SetYRot(owner->transformable.GetYRot()+rotationSpeed*deltaTime);
		}
		owner->transformable.SetXRot(owner->transformable.GetXRot()+(rotationSpeed*1.5f)*deltaTime);
		break;
	case LEFT:
		if(owner->transformable.GetYRot() > -90.0f)
		{
			owner->transformable.SetYRot(owner->transformable.GetYRot()-rotationSpeed*deltaTime);
		}
		owner->transformable.SetXRot(owner->transformable.GetXRot()+(rotationSpeed*1.5f)*deltaTime);
		break;
	case UP:
		if(owner->transformable.GetXRot() > -90.0f)
		{
			owner->transformable.SetXRot(owner->transformable.GetXRot()-rotationSpeed*deltaTime);
		}
		owner->transformable.SetZRot(owner->transformable.GetZRot()-(rotationSpeed*1.5f)*deltaTime);
		break;
	case DOWN:
		if(owner->transformable.GetXRot() < 90.0f)
		{
			owner->transformable.SetXRot(owner->transformable.GetXRot()+rotationSpeed*deltaTime);
		}
		owner->transformable.SetZRot(owner->transformable.GetZRot()-(rotationSpeed*1.5f)*deltaTime);
		break;
	}
}
