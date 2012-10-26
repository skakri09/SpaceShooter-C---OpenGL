#include "SpaceShip.h"

SpaceShip::SpaceShip(int spaceshipHP)
	:log("SpaceShipbase", WARN)
{
	this->SpaceShipMaxHealth = spaceshipHP;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Update(float deltaTime)
{
	if(SpaceShipCurrentHealth > 0)
	{
		transformable.Update(deltaTime);
		collisionSphere.Update(transformable.GetCollisionTransformationInfo());
		shooterModule.UpdateModule(deltaTime);
	}
	else
	{
		//KillGameObject();
	}
}

void SpaceShip::Draw()
{
	vboDrawable.DrawWithArrays();
}

void SpaceShip::CreateGameObject(std::string meshPathFrom3dsFolder)
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::string meshPath = "..//3ds//";
		meshPath += meshPathFrom3dsFolder;
		MeshInfo meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

		vboDrawable.SetMeshInfo(meshInfo);
		collisionSphere = *meshInfo.collisionSphere;
	}
}

void SpaceShip::FireGun(ProjectileTypes projectileType)
{
	shooterModule.Shoot(projectileType,
		*transformable.getPosition(),
		transformable.getDirectionVector());
}

void SpaceShip::InitSpaceShip( float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ, float scale)
{
	Vector3D startPos(startX, startY, startZ);
	Vector3D rotationAxis(rotX, rotY, rotZ);
	Vector3D directionVec(dirVecX, dirVecY, dirVecZ);

	transformable.Init(startPos,rotationAxis, startRotDeg, scale, directionVec);

	SpaceShipCurrentHealth = SpaceShipMaxHealth;
}

void SpaceShip::HandleProjectileCollision( std::deque<std::shared_ptr<Projectile>>* projectiles )
{
	for(unsigned int i = 0; i < projectiles->size(); i++)
	{
		if(projectiles->at(i)->isFired())
		{
			BoundingSphere projectileColSphere = projectiles->at(i)->GetCollisionSphere();
			Vector3D collAmnt = collisionSphere.IsCollision(projectileColSphere);
			if(collAmnt.getX() > 0 || collAmnt.getY() > 0.0f || collAmnt.getZ() > 0.0f)
			{
				int dmgTaken = projectiles->at(i)->GetProjectileDmg();
				SpaceShipCurrentHealth -= dmgTaken;
				log << WARN << "Spaceship hit! It lost " << dmgTaken << ", " 
					<< SpaceShipCurrentHealth << "/" << SpaceShipMaxHealth <<"HP left" << std::endl;
				projectiles->at(i)->DestroyProjectile();
			}
		}
	}
}
