#include "PlayerSpaceShip.h"


PlayerSpaceShip::PlayerSpaceShip()
	: log("PlayerSpaceship", ERRORX),
	SpaceShip(50)//the HP
{
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

void PlayerSpaceShip::Draw()
{
	glPushMatrix();
	
	ApplyTransformations();
	glRotatef(180, 0, 0, 1);//sortof placeholder rotation
	DrawWithArrays();

	glPopMatrix();
	shooterModule.DrawModule();
}

void PlayerSpaceShip::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);	
	shooterModule.UpdateModule(deltaTime);
	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void PlayerSpaceShip::CreateGameObject()
{
	meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//MilleniumFalcon//MilleniumFalcon.3ds");
	collisionSphere = *meshInfo.collisionSphere;//*loader.GetBoundingSphere();
	WasInited = true;
}

void PlayerSpaceShip::Shoot()
{
	SpaceShip::FireGun(SQUARE_FAST_BULLET);
}

void PlayerSpaceShip::InitSpaceship( float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceship(startX, startY, startZ,
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);
	GameObject::SetScale(0.5f, 0.5f, 0.5f);

	if(!WasInited)
	{
		CreateGameObject();
	}
}

