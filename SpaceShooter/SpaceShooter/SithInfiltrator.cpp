#include "SithInfiltrator.h"

SithInfiltrator::SithInfiltrator(PlayerSpaceShip* playerShip)
	: log("SithInfiltrator", WARN),
	 BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
					std::make_shared<EnemySpaceshipConstantState>(),
					10)//hp
	
{
}

SithInfiltrator::~SithInfiltrator()
{
}

void SithInfiltrator::Draw()
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

void SithInfiltrator::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	shooterModule.UpdateModule(deltaTime);
	HandleAI();

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void SithInfiltrator::CreateGameObject()
{
	meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//SithInfiltrator//SithInfiltrator.3ds");
	collisionSphere = *meshInfo.collisionSphere;
	WasInited = true;
}

void SithInfiltrator::Shoot()
{
 	SpaceShip::FireGun();
}

void SithInfiltrator::InitSpaceship(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);

	GameObject::SetScale(0.05f, 0.05f, 0.05f);
	BaseEnemyShip::ShipSpeed = 75;
	if(!WasInited)
	{
		CreateGameObject();
	}
}

void SithInfiltrator::HandleAI()
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
	