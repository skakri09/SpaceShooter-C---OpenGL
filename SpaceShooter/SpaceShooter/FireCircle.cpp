#include "FireCircle.h"

FireCircle::FireCircle()
	:log("FireCircle", INFO),AiState("FireCircle")
{

}

void FireCircle::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering FireCircle" << std::endl;
	
	fireDirectionVec.setValues(1.0f, 0.0f, 1.0f);
}

void FireCircle::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	trans = owner->transformable;

	trans.SetDirectionVector(fireDirectionVec.getX(), fireDirectionVec.getY(), fireDirectionVec.getZ());
	if(owner->shooterModule.Shoot(LASER_WALL, trans, owner))
	{
		fireDirectionVec.setX(fireDirectionVec.getX()-0.1f);
	}

	if(fireDirectionVec.getX() <= -1.0f)
	{
		owner->GetAiStateMachine().ChangeState(std::make_shared<StarDestroyerBossFight>());
	}
}

void FireCircle::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting FireCircle" << std::endl;
}

