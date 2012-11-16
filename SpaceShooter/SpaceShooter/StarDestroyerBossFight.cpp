#include "StarDestroyerBossFight.h"
#include "SpaceShipManager.h"
#include "SoundManager.h"

void StarDestroyerBossFight::Enter( BaseEnemyShip* owner )
{
	log << WARN << "Entering StarDestroyerBossFight" << std::endl;
	SpaceShipManager::Inst()->GetStarDestroyer()->EnableFightMode();
	shotsFired = 0;	
	chargeUpPlayed = false;
}

void StarDestroyerBossFight::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	if(owner->Shoot(PLAYER_SEEKING_LASER))
	{
		SoundManager::Inst()->PlayEffect(3, "star_destroyer_laser", 50);
		shotsFired++;
	}
	if(shotsFired >= 6)
	{
		if(!chargeUpPlayed)
		{
			SoundManager::Inst()->PlayEffect(2, "star_destroyer_charge", 50);
			chargeUpPlayed = true;
		}
	}
	if(shotsFired >= 10)
	{
		owner->GetAiStateMachine().ChangeState(std::make_shared<FireCircle>());
	}
}

void StarDestroyerBossFight::Exit( BaseEnemyShip* owner )
{
	log << WARN << "Exiting StarDestroyerBossFight" << std::endl;
}
