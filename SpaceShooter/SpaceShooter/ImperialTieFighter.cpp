#include "ImperialTieFighter.h"


ImperialTieFighter::ImperialTieFighter(PlayerSpaceShip* playerShip)
	: log("ImperialTieFighter", WARN),
	BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
	std::make_shared<EnemySpaceshipConstantState>(),
	20)//hp
{
}

ImperialTieFighter::~ImperialTieFighter()
{
}

void ImperialTieFighter::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	shooterModule.UpdateModule(deltaTime);
}

void ImperialTieFighter::InitSpaceShip(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 0.8f);

	CreateGameObject("ImperialTieFighter//ImperialTieFighter.3ds");
	aiStateMachine.ChangeState(std::make_shared<ApproachRandXYPos>());
}
