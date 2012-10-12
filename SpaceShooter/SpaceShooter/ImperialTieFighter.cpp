#include "ImperialTieFighter.h"


ImperialTieFighter::ImperialTieFighter(PlayerSpaceShip* playerShip)
	: log("ImperialTieFighter", WARN),
	BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
	std::make_shared<EnemySpaceshipConstantState>(),
	10)//hp
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
 	SpaceShip::FireGun();
}

void ImperialTieFighter::InitSpaceship(float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);

	GameObject::SetScale(1.05f, 1.05f, 1.05f);

	if(!WasInited)
	{
		CreateGameObject();
	}
}

void ImperialTieFighter::HandleAI()
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
	