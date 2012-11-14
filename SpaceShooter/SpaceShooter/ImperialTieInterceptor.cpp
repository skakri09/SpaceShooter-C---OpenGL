#include "ImperialTieInterceptor.h"

ImperialTieInterceptor::ImperialTieInterceptor(std::shared_ptr<PlayerSpaceShip> playerShip)
	: log("ImperialTieInterceptor", WARN),
	 BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
					std::make_shared<EnemySpaceshipConstantState>(),
					10, IMPERIAL_TIE_INTERCEPTOR)//hp
	
{

}

ImperialTieInterceptor::~ImperialTieInterceptor()
{
}


void ImperialTieInterceptor::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
}

void ImperialTieInterceptor::InitSpaceShip(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 0.5f);

	CreateGameObject("ImperialTieInterceptor//ImperialTieInterceptor.3ds");
	aiStateMachine.ChangeState(std::make_shared<ApproachEdge>());
}

void ImperialTieInterceptor::Draw()
{
	aabb.DrawAABB();
	glColor4f(0.1f, 0.1f, 0.15f, 1.0f);
	BaseEnemyShip::Draw();
	glColor4f(1, 1, 1, 1);
}

