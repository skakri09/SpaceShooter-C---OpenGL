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

void SithInfiltrator::Shoot()
{
 	SpaceShip::FireGun(SQUARE_SLOW_BULLET);
}

void SithInfiltrator::InitSpaceShip(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	BaseEnemyShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);

	GameObject::SetScale(0.05f, 0.05f, 0.05f);
	BaseEnemyShip::ShipSpeed = 50;

	CreateGameObject("SithInfiltrator//SithInfiltrator.3ds");

}

void SithInfiltrator::HandleAI()
{
	float xyDist = position.XYDistance(*playerShip->getPosition());
	if(aiStateMachine.GetCurrentState() != "ApproachXYZPlayerState"
		&& position.getZ() < -75 && aiStateMachine.GetCurrentState() != "ApproachXYPlayerState")
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
	