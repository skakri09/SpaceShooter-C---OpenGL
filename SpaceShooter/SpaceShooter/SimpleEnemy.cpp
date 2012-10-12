#include "SimpleEnemy.h"

SithInfiltratorEnemy::SithInfiltratorEnemy(PlayerSpaceShip* playerShip)
	: log("SimpleEnemy", WARN),
	 BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
					std::make_shared<EnemySpaceshipConstantState>(),
					10)//hp
	
{
}

SithInfiltratorEnemy::~SithInfiltratorEnemy()
{
}

void SithInfiltratorEnemy::Draw()
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

void SithInfiltratorEnemy::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	shooterModule.UpdateModule(deltaTime);
	HandleAI();

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void SithInfiltratorEnemy::CreateGameObject()
{
	meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//SithInfiltrator//SithInfiltrator.3ds");
	collisionSphere = *meshInfo.collisionSphere;
	WasInited = true;
}

void SithInfiltratorEnemy::Shoot()
{
 	SpaceShip::FireGun();
}

void SithInfiltratorEnemy::InitSpaceship(float startX, float startY, float startZ,
	float scaleX, float scaleY, float scaleZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ,
		scaleX, scaleY, scaleZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);

	if(!WasInited)
	{
		CreateGameObject();
	}
}

void SithInfiltratorEnemy::HandleAI()
{
		
	float a = position.Distance(*playerShip->getPosition());
	if(a >= 105 && aiStateMachine.GetCurrentState() != "FollowPlayerState")
	/*if(position.getX() <= (playerShip->getXPos()+50)
		&& aiStateMachine.GetCurrentState() != "FollowPlayerState")*/
	{
		aiStateMachine.ChangeState(std::make_shared<FollowPlayerState>());
	}
	//else if(position.getX() >= (playerShip->getXPos()-50)
	//	&& aiStateMachine.GetCurrentState() != "FollowPlayerState")
	//{
	//	aiStateMachine.ChangeState(std::make_shared<FollowPlayerState>());
	//}
	//else if(aiStateMachine.GetCurrentState() != "FireState"
	//	&& ( position.getX() <= (playerShip->getXPos()+50) 
	//	|| position.getX() >= (playerShip->getXPos()-50)))
	else if(aiStateMachine.GetCurrentState() != "FireState"
		&& a < 110)
	{
		aiStateMachine.ChangeState(std::make_shared<FireState>());
	}
}
	