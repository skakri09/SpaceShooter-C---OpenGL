#include "StarDestroyerShipSpawning.h"

StarDestroyerShipSpawning::StarDestroyerShipSpawning()
	:log("StarDestroyerShipSpawning", WARN),
	AiState("StarDestroyerShipSpawning")
{
	lastImpInterceptorSpawn = 0.0f;
	lastImpTieFighterSpawn = 0.0f;
}

void StarDestroyerShipSpawning::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering StarDestroyerShipSpawning" << std::endl;
	direction = LEFT;
	owner->transformable.setXVel(20.0f);
	ownerShip = owner;
	totalShipsSpawned = 0;
}

void StarDestroyerShipSpawning::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	log << INFO << "--" << std::endl;
	UpdateDirection(owner);
	HandleShipSpawning(deltaTime);
	if(totalShipsSpawned >= 5)
	{	
		owner->GetAiStateMachine().ChangeState(
			std::make_shared<ApproachGivenPosition>
			( 
				0.0f, -10.0f, -150.0f, 50.0f, std::make_shared<StarDestroyerBossFight>()
			));
	}
}

void StarDestroyerShipSpawning::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting StarDestroyerShipSpawning" << std::endl;
}

void StarDestroyerShipSpawning::UpdateDirection( BaseEnemyShip* owner )
{
	if(direction == RIGHT && owner->transformable.getXPos() >= 200)
	{
		direction = DOWN;
		owner->transformable.setXVel(0.0f);
		owner->transformable.setYVel(20.0f);
	}
	if(direction == DOWN && owner->transformable.getYPos() >= 200)
	{
		direction = LEFT;
		owner->transformable.setXVel(-20.0f);
		owner->transformable.setYVel(0.0f);
	}
	if(direction == LEFT && owner->transformable.getXPos() <= -200)
	{
		direction = UP;
		owner->transformable.setXVel(0.0f);
		owner->transformable.setYVel(-20.0f);
	}
	if(direction == UP && owner->transformable.getYPos() <= -200)
	{
		direction = RIGHT;
		owner->transformable.setXVel(20.0f);
		owner->transformable.setYVel(0.0f);
	}
	
}

void StarDestroyerShipSpawning::HandleShipSpawning( float deltaTime )
{
	lastImpInterceptorSpawn += deltaTime;
	lastImpTieFighterSpawn += deltaTime;

	if(lastImpTieFighterSpawn >= 1.5f)
	{
		lastImpTieFighterSpawn = 0.0f;
		std::shared_ptr<ImperialTieFighter> ship = std::make_shared<ImperialTieFighter>
			(SpaceShipManager::Inst()->GetPlayer());
		float x = ownerShip->transformable.getXPos();
		float y = ownerShip->transformable.getYPos();
		float z = ownerShip->transformable.getZPos();
		ship->InitSpaceShip(x, y, z, 0, 0, 0, 0, 0, 0, 1);
		SpaceShipManager::Inst()->TransferShipToShipManager(ship);
		totalShipsSpawned++;
	}
	if(lastImpInterceptorSpawn >= 2.0f)
	{
		lastImpInterceptorSpawn = 0.0f;
		std::shared_ptr<ImperialTieInterceptor> ship = std::make_shared<ImperialTieInterceptor>
			(SpaceShipManager::Inst()->GetPlayer());
		float x = ownerShip->transformable.getXPos();
		float y = ownerShip->transformable.getYPos();
		float z = ownerShip->transformable.getZPos();
		ship->InitSpaceShip(x, y, z, 0, 0, 0, 0, 0, 0, 1);
		SpaceShipManager::Inst()->TransferShipToShipManager(ship);
		totalShipsSpawned++;
	}
}

