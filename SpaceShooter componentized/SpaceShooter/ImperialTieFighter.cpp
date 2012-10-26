#include "ImperialTieFighter.h"


ImperialTieFighter::ImperialTieFighter(PlayerSpaceShip* playerShip)
	: log("ImperialTieFighter", WARN),
	BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
	std::make_shared<EnemySpaceshipConstantState>(),
	30)//hp
{
}

ImperialTieFighter::~ImperialTieFighter()
{
}

void ImperialTieFighter::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	shooterModule.UpdateModule(deltaTime);
	HandleAI();

}

void ImperialTieFighter::Shoot()
{
 	SpaceShip::FireGun(SQUARE_SLOW_BULLET);
}

void ImperialTieFighter::InitSpaceShip(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 1.05f);

	BaseEnemyShip::ShipSpeed = 50;

	CreateGameObject("ImperialTieFighter//ImperialTieFighter.3ds");
}

void ImperialTieFighter::HandleAI()
{
	float xyDist = transformable.getPosition()->XYDistance(*playerShip->transformable.getPosition());

	if(aiStateMachine.GetCurrentState() != "ApproachXYZPlayerState"
		&& transformable.getPosition()->getZ() < -75)
	{
		aiStateMachine.ChangeState(std::make_shared<ApproachXYZPlayerState>());
	}
	else if(xyDist > 30 && aiStateMachine.GetCurrentState() != "ApproachXYPlayerState"
		&& transformable.getPosition()->getZ()>=-75)
	{
		aiStateMachine.ChangeState(std::make_shared<ApproachXYPlayerState>());
	}
	else if(aiStateMachine.GetCurrentState() != "FireState" && xyDist <= 30
		&& transformable.getPosition()->getZ() >=-75)
	{
		aiStateMachine.ChangeState(std::make_shared<FireState>());
	}
}
	