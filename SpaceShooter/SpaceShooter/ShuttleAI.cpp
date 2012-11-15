#include "ShuttleAI.h"

ShuttleAI::ShuttleAI()
	:log("ShuttleAI", INFO),AiState("ShuttleAI")
{
	dsStartPos.setValues(-700, 200, -750);
	leftTargetPos.setValues(FRUSTUM_LEFT, GetRandFloat(FRUSTUM_BOTTOM, FRUSTUM_BOTTOM), -100.0f);
	rightTargetPos.setValues(FRUSTUM_RIGHT, GetRandFloat(FRUSTUM_BOTTOM, FRUSTUM_BOTTOM), -100.0f);
	planetTargetPos.setValues(800, -400, -700);

	startVel = leftTargetPos - dsStartPos;
	startVel.Normalize(); 
	startVel*= 100.0f;

	leftToRightVel = rightTargetPos - leftTargetPos;
	leftToRightVel.Normalize();
	leftToRightVel *= 50.0f;

	flyOutVel = planetTargetPos - rightTargetPos;
	flyOutVel.Normalize();
	flyOutVel *= 150.0f;
}

void ShuttleAI::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ShuttleAI" << std::endl;
	owner->transformable.SetPos(dsStartPos);
}

void ShuttleAI::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	log << INFO << "--" << std::endl;
}

void ShuttleAI::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ShuttleAI" << std::endl;
}

