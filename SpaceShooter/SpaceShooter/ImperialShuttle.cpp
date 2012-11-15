#include "ImperialShuttle.h"


ImperialShuttle::ImperialShuttle( std::shared_ptr<PlayerSpaceShip> playerShip, 
	ProjectileTypes cargo)
	: log("ImperialStarShuttle", WARN),
	BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
	std::make_shared<EnemySpaceshipConstantState>(),
	20, IMPERIAL_SHUTTLE)//hp
{
	this->cargo = cargo;
}

ImperialShuttle::~ImperialShuttle()
{

}

void ImperialShuttle::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	if(killedByPlayer)
	{
		SpaceShipManager::Inst()->SpawnProjectilePowerup(cargo, transformable.getPosition());
	}
}

void ImperialShuttle::Draw()
{
	glColor4f(0.2f, 0.5f, 0.2f, 1.0f);
	glPushMatrix();

	transformable.ApplyGLTransformations();
	vboDrawable.Draw();

	glPopMatrix();
	glColor4f(1, 1, 1, 1);
}

void ImperialShuttle::InitSpaceShip( float startX, float startY, float startZ, float startRotDeg, float rotX, float rotY, float rotZ, float dirVecX, float dirVecY, float dirVecZ )
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 0.3f);

	CreateGameObject("ImperialShuttle//ImperialShuttle.3ds");

	float randX = GetRandFloat(-5.0f, 5.0f);
	float randY = GetRandFloat(-5.0f, 5.0f);
	aiStateMachine.ChangeState
	(
		std::make_shared<ShuttleAI>()
	);
}
