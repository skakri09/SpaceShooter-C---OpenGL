#include "ImperialStarDestroyer.h"


ImperialStarDestroyer::ImperialStarDestroyer(PlayerSpaceShip* playerShip)
	:log("ImperialStarDestroyerInactiveState", WARN),
	BaseEnemyShip(playerShip, std::make_shared<StarDestroyerShipSpawning>(),
	std::make_shared<EnemySpaceshipConstantState>(), 1000)
{
}

ImperialStarDestroyer::~ImperialStarDestroyer()
{

}

void ImperialStarDestroyer::Draw()
{
	if(isAlive)
	{
		glPushMatrix();

		ApplyTransformations();

		DrawWithArrays();

		glPopMatrix();
		//shooterModule.DrawModule();
	}
}

void ImperialStarDestroyer::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	//shooterModule.UpdateModule(deltaTime);
	HandleAI();
}

void ImperialStarDestroyer::InitSpaceShip( float startX, float startY, float startZ, float startRotDeg, float rotX, float rotY, float rotZ, float dirVecX, float dirVecY, float dirVecZ )
{
	BaseEnemyShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);
	BaseEnemyShip::ShipSpeed = 50;
	GameObject::SetScale(0.4f, 0.4f, 0.4f);

	if(!WasInited)
	{
		CreateGameObject("ImperialStarDestroyer//ImperialStarDestroyer.3ds");
	}
}

void ImperialStarDestroyer::Shoot()
{

}

void ImperialStarDestroyer::HandleAI()
{

}

