#include "ImperialStarDestroyer.h"


ImperialStarDestroyer::ImperialStarDestroyer(std::shared_ptr<PlayerSpaceShip> playerShip)
	:log("ImperialStarDestroyerInactiveState", WARN),
	BaseEnemyShip(playerShip, std::make_shared<StarDestroyerShipSpawning>(),
	std::make_shared<EnemySpaceshipConstantState>(), 10000, IMPERIAL_STAR_DESTROYER)
{
}

ImperialStarDestroyer::~ImperialStarDestroyer()
{

}

void ImperialStarDestroyer::Update( GLfloat deltaTime )
{
	aiStateMachine.Update(deltaTime);
	transformable.Update(deltaTime);
	aabb.Update(transformable.GetCollisionTransformationInfo());
	shooterModule.UpdateModule(deltaTime);
	
	if(SpaceShipCurrentHealth <= 0)
	{
		GameObject::FlagForKill();
		killedByPlayer = true;
	}
}

void ImperialStarDestroyer::InitSpaceShip( float startX, float startY, float startZ, float startRotDeg, float rotX, float rotY, float rotZ, float dirVecX, float dirVecY, float dirVecZ )
{
	SpaceShip::InitSpaceShip(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ, 1.5f);

	CreateGameObject("ImperialStarDestroyer//ImperialStarDestroyer.3ds");
}

void ImperialStarDestroyer::Draw()
{
	glColor3f(0.7f, 0.7f, 0.7f);
	BaseEnemyShip::Draw();
	glColor3f(1, 1, 1);
}

void ImperialStarDestroyer::CreateGameObject( std::string meshPathFrom3dsFolder )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::string meshPath = "..//3ds//";
		meshPath += meshPathFrom3dsFolder;
		std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

		vboDrawable.SetMeshInfo(meshInfo);
		//Creating sub boxes
		CreateStarDestroyerSubBoxes(meshInfo->aabb);
		aabb = *meshInfo->aabb;
	}
}

void ImperialStarDestroyer::CreateStarDestroyerSubBoxes(std::shared_ptr<AABBCollisionBox> orgAABB)
{
	orgAABB->CreateSubBox( std::make_shared<AABBCollisionBox>(-2.0f, 2.0f, -8.0f, -3.5f, -21.43f, 70.5f));//middle long

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-5.0f, -2.0f, -8.0f, -3.5f, -21.43f, 60.0f)); //left long
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(2.0f, 5.0f, -8.0f, -3.5f, -21.43f, 60.0f));//right long
	
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-8.0f, -5.0f, -8.0f, -3.5f, -21.43f, 50.0f)); //left long2
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(5.0f, 8.0f, -8.0f, -3.5f, -21.43f, 50.0f));//right long2

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-12.0f, -8.0f, -8.0f, -3.5f, -21.43f, 35.0f)); //left long3
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(8.0f, 12.0f, -8.0f, -3.5f, -21.43f, 35.0f));//right long3

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-15.0f, -12.0f, -8.0f, -3.5f, -18.43f, 20.0f)); //left long4
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(12.0f, 15.0f, -8.0f, -3.5f, -18.43f, 20.0f));//right long4

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-18.0f, -15.0f, -8.0f, -3.5f, -18.43f, 10.0f)); //left long5
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(15.0f, 18.0f, -8.0f, -3.5f, -18.43f, 10.0f));//right long5

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-21.0f, -18.0f, -8.0f, -3.5f, -17.43f, 0.0f)); //left long6
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(18.0f, 21.0f, -8.0f, -3.5f, -17.43f, 0.0f));//right long6

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-25.0f, -21.0f, -8.0f, -3.5f, -16.43f, -10.0f)); //left long7
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(21.0f, 25.0f, -8.0f, -3.5f, -16.43f, -10.0f));//right long7

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-10.0f, 10.0f, -3.5f, 12.0f, -21.43f, -5.0f)); //Back middle-top

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-10.0f, 10.0f, -10.0f, -8.0f, -21.43f, 20.0f)); //Back  bottom
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-5.0f, 5.0f, -13.0f, -10.0f, -21.43f, 5.0f)); //Back  bottom2

	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-10.0f, 10.0f, -3.5f, 0.0f, -5.0f, 22.0f));//middle tier1
	orgAABB->CreateSubBox(std::make_shared<AABBCollisionBox>(-10.0f, 10.0f, 0.0f, 4.0f, -5.0f, 13.0f));//middle tier2
}
