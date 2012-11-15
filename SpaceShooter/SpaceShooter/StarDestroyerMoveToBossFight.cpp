#include "StarDestroyerMoveToBossfight.h"

void StarDestroyerMoveToBossfight::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering StarDestroyerMoveToBossFight" << std::endl;
	targetPos.setValues(0.0f, -10.0f, -180.0f);
	velocity = targetPos - *owner->transformable.getPosition();
	velocity.Normalize();
	velocity*=50.0f;
	owner->transformable.SetVelocity(velocity);
}

void StarDestroyerMoveToBossfight::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	float dist = owner->transformable.getPosition()->Distance(targetPos);

	if(dist <= 40)
	{
		Vector3D newVel = velocity;
		newVel*=(dist/40);
		owner->transformable.SetVelocity(newVel);
		if(dist <= 4)
		{
			owner->GetAiStateMachine().ChangeState(std::make_shared<StarDestroyerBossFight>());
		}
	}
}

void StarDestroyerMoveToBossfight::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting StarDestroyerMoveToBossFight" << std::endl;
	owner->transformable.SetVelocity(0, 0, 0);
}
