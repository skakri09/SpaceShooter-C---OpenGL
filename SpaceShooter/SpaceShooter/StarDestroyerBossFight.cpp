#include "StarDestroyerBossFight.h"
#include "SpaceShipManager.h"

void StarDestroyerBossFight::Enter( BaseEnemyShip* owner )
{
	log << WARN << "Entering StarDestroyerBossFight" << std::endl;
	SpaceShipManager::Inst()->GetStarDestroyer()->EnableFightMode();
	
}

void StarDestroyerBossFight::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	owner->GetAiStateMachine().ChangeState(std::make_shared<FireCircle>());
}

void StarDestroyerBossFight::Exit( BaseEnemyShip* owner )
{
	log << WARN << "Exiting StarDestroyerBossFight" << std::endl;
}
