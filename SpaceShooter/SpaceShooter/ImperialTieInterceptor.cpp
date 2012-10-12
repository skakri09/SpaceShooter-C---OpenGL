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

void ImperialTieInterceptor::Draw()
{
	if(isAlive)
	{
		glPushMatrix();

		ApplyTransformations();

		DrawWithArrays();

		glPopMatrix();
		shooterModule.DrawModule();
	}
}

void ImperialTieInterceptor::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	shooterModule.UpdateModule(deltaTime);
	HandleAI();

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void ImperialTieInterceptor::CreateGameObject()
{
	meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//ImperialTieInterceptor//ImperialTieInterceptor.3ds");
	collisionSphere = *meshInfo.collisionSphere;
	WasInited = true;
}

void ImperialTieInterceptor::Shoot()
{
 	SpaceShip::FireGun();
}

void ImperialTieInterceptor::InitSpaceship(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);
	BaseEnemyShip::ShipSpeed = 75;
	GameObject::SetScale(0.7f, 0.7f, 0.7f);

	if(!WasInited)
	{
		CreateGameObject();
	}
}

void ImperialTieInterceptor::HandleAI()
{
	float dist = position.Distance(*playerShip->getPosition());
	if(dist >= 105 && aiStateMachine.GetCurrentState() != "ApproachXYZPlayerState"
		&& position.getZ() > -50)
	{
		aiStateMachine.ChangeState(std::make_shared<ApproachXYZPlayerState>());
	}
	else if(dist > 75 && aiStateMachine.GetCurrentState() != "ApproachXYPlayerState")
	{
		aiStateMachine.ChangeState(std::make_shared<ApproachXYPlayerState>());
	}
	else if(aiStateMachine.GetCurrentState() != "FireState")
	{
		aiStateMachine.ChangeState(std::make_shared<FireState>());
	}
}
	