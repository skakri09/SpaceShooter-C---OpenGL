#include "ImperialStarDestroyer.h"


ImperialStarDestroyer::ImperialStarDestroyer(std::shared_ptr<PlayerSpaceShip> playerShip)
	:log("ImperialStarDestroyerInactiveState", WARN),
	BaseEnemyShip(playerShip, std::make_shared<StarDestroyerShipSpawning>(),
	std::make_shared<EnemySpaceshipConstantState>(), 1000, IMPERIAL_STAR_DESTROYER)
{
}

ImperialStarDestroyer::~ImperialStarDestroyer()
{

}

void ImperialStarDestroyer::Update( GLfloat deltaTime )
{
	//BaseEnemyShip::Update(deltaTime);
}

void ImperialStarDestroyer::InitSpaceShip( float startX, float startY, float startZ, float startRotDeg, float rotX, float rotY, float rotZ, float dirVecX, float dirVecY, float dirVecZ )
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 1.0f);

	CreateGameObject("ImperialStarDestroyer//ImperialStarDestroyer.3ds");
	BaseEnemyShip::Update(0.1f);
}

void ImperialStarDestroyer::Draw()
{
	//glColor3f(0.5f, 0.5f, 0.5f);
	BaseEnemyShip::Draw();
	glColor3f(1, 1, 1);
}
