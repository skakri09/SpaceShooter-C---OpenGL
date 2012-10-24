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


void ImperialTieFighter::Draw()
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

void ImperialTieFighter::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	shooterModule.UpdateModule(deltaTime);
	HandleAI();

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void ImperialTieFighter::CreateGameObject()
{
	meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//ImperialTieFighter//ImperialTieFighter.3ds");
	collisionSphere = *meshInfo.collisionSphere;
	WasInited = true;
}

void ImperialTieFighter::Shoot()
{
 	SpaceShip::FireGun(SQUARE_SLOW_BULLET);
}

void ImperialTieFighter::InitSpaceship(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);
	BaseEnemyShip::ShipSpeed = 50;
	GameObject::SetScale(1.05f, 1.05f, 1.05f);

	if(!WasInited)
	{
		CreateGameObject();
	}
}

void ImperialTieFighter::HandleAI()
{
	float xyDist = position.XYDistance(*playerShip->getPosition());
	if(aiStateMachine.GetCurrentState() != "ApproachXYZPlayerState"
		&& position.getZ() < -75)
	{
		aiStateMachine.ChangeState(std::make_shared<ApproachXYZPlayerState>());
	}
	else if(xyDist > 30 && aiStateMachine.GetCurrentState() != "ApproachXYPlayerState"
		&& position.getZ()>=-75)
	{
		aiStateMachine.ChangeState(std::make_shared<ApproachXYPlayerState>());
	}
	else if(aiStateMachine.GetCurrentState() != "FireState" && xyDist <= 30
		&& position.getZ() >=-75)
	{
		aiStateMachine.ChangeState(std::make_shared<FireState>());
	}
}
	