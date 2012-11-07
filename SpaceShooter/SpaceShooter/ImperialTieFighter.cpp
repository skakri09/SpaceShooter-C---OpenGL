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
	aiStateMachine.ChangeState(std::make_shared<ApproachRandXYPos>());
}

void ImperialTieFighter::HandleAI()
{
	//if(aiStateMachine.GetCurrentState() != "ApproachRandXYPos")
	//{
	//	
	//}
	/*else if(aiStateMachine.GetCurrentState() != "FireState" && transformable.getZPos() == -60.0f)
	{
		aiStateMachine.ChangeState(std::make_shared<FireState>());
	}	*/
}
	