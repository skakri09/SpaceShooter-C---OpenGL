#include "ShuttleAI.h"

ShuttleAI::ShuttleAI()
	:log("ShuttleAI", INFO),AiState("ShuttleAI")
{
	dsStartPos.setValues(-700, 200, -750);
	leftTargetPos.setValues(FRUSTUM_LEFT, GetRandFloat(FRUSTUM_BOTTOM, FRUSTUM_BOTTOM), -100.0f);
	rightTargetPos.setValues(FRUSTUM_RIGHT, GetRandFloat(FRUSTUM_BOTTOM, FRUSTUM_BOTTOM), -100.0f);
	planetTargetPos.setValues(700, -700, -1100);

	startVel = leftTargetPos - dsStartPos;
	startVel.Normalize(); 
	startVel*= 100.0f;
}

void ShuttleAI::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ShuttleAI" << std::endl;
	owner->transformable.SetPos(dsStartPos);
	owner->transformable.SetVelocity(startVel);
	currentTarget = &leftTargetPos;
	currentVelocity = &startVel;
	curTravelPart = TO_SCREEN_LEFT;
	log << WARN << "Travelpart = TO_SCREEN_LEFT" << std::endl;
}

void ShuttleAI::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	float dist = owner->transformable.getPosition()->Distance(*currentTarget);
	
	if(curTravelPart == TO_SCREEN_LEFT || curTravelPart == TO_PLANET)
	{
		if(dist <= 60)
		{
			Vector3D newVel = *currentVelocity;
			newVel*= (dist/60);
			owner->transformable.SetVelocity(newVel);
			if(dist <= 5)
			{
				if(curTravelPart == TO_SCREEN_LEFT)
				{
					SetLeftToRightState(owner);	
				}
				else if(curTravelPart == TO_PLANET)
				{
					log << WARN << "Travelpart = finished, killing" << std::endl;
					owner->GetAiStateMachine().ChangeState(std::make_shared<KillOwnerState>());
				}
			}
		}
	}
	else //curtravelpart == TO_SCREN_RIGHT
	{
		if(dist <= 5)
		{
			Vector3D newVel = *currentVelocity;
			newVel*= (dist/5);
			owner->transformable.SetVelocity(newVel);
			if(dist <= 1)
			{
				SetRightToPlanetState(owner);
			}
		}
	}
}

void ShuttleAI::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ShuttleAI" << std::endl;
}

void ShuttleAI::SetLeftToRightState(BaseEnemyShip* owner)
{
	curTravelPart = TO_SCREEN_RIGHT;
	log << WARN << "Travelpart = to_screen_right" << std::endl;

	leftToRightVel = rightTargetPos - *owner->transformable.getPosition();
	leftToRightVel.Normalize();
	leftToRightVel *= 25.0f;
	owner->transformable.SetVelocity(leftToRightVel);
	currentTarget = &rightTargetPos;
	currentVelocity = &leftToRightVel;
}

void ShuttleAI::SetRightToPlanetState( BaseEnemyShip* owner )
{
	log << WARN << "Travelpart = PLANET" << std::endl;
	curTravelPart = TO_PLANET;

	flyOutVel = planetTargetPos - *owner->transformable.getPosition();
	flyOutVel.Normalize();
	flyOutVel *= 150.0f;
	owner->transformable.SetVelocity(flyOutVel);
	currentTarget = &planetTargetPos;
	currentVelocity = &flyOutVel;
}

void ShuttleAI::SetRotation( BaseEnemyShip* enemy )
{
	switch(curTravelPart)
	{
	case TO_SCREEN_LEFT:

		break;
	case TO_SCREEN_RIGHT:
		
		break;
	case TO_PLANET:

		break;
	}
}
