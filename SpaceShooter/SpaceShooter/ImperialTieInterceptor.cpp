#include "ImperialTieInterceptor.h"

ImperialTieInterceptor::ImperialTieInterceptor(PlayerSpaceShip* playerShip)
	: log("ImperialTieInterceptor", WARN),
	 BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
					std::make_shared<EnemySpaceshipConstantState>(),
					10)//hp
	
{

}

ImperialTieInterceptor::~ImperialTieInterceptor()
{
}


void ImperialTieInterceptor::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	//shooterModule.UpdateModule(deltaTime);
	HandleAI();

}

void ImperialTieInterceptor::Shoot()
{
 	SpaceShip::FireGun(SQUARE_SLOW_BULLET);
}

void ImperialTieInterceptor::InitSpaceShip(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 0.7f);

	BaseEnemyShip::ShipSpeed = 75;

	CreateGameObject("ImperialTieInterceptor//ImperialTieInterceptor.3ds");
}

void ImperialTieInterceptor::HandleAI()
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
	