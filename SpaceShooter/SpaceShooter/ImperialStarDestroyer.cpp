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

void ImperialStarDestroyer::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
}

void ImperialStarDestroyer::InitSpaceShip( float startX, float startY, float startZ, float startRotDeg, float rotX, float rotY, float rotZ, float dirVecX, float dirVecY, float dirVecZ )
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 0.4f);

	BaseEnemyShip::ShipSpeed = 50;

	CreateGameObject("ImperialStarDestroyer//ImperialStarDestroyer.3ds");
}
