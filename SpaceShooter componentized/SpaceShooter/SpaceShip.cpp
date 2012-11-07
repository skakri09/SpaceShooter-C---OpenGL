#include "SpaceShip.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;
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
	transformable.Update(deltaTime);
	collisionSphere.Update(transformable.GetCollisionTransformationInfo());
	shooterModule.UpdateModule(deltaTime);

	if(SpaceShipCurrentHealth <= 0)
	{
		GameObject::FlagForKill();
	}
}

void SpaceShip::Draw()
{
	if(IsAlive())
	{
		transformable.ApplyGLTransformations();
		vboDrawable.Draw();
	}
	
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
	shooterModule.Shoot(projectileType, transformable, this);
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

void SpaceShip::HandleProjectileCollision( std::shared_ptr<Projectile> projectile )
{
	if(projectile->isFired())
	{
		BoundingSphere projectileColSphere = projectile->collisionSphere;
		Vector3D collAmnt = collisionSphere.IsCollision(projectileColSphere);
		if(collAmnt.getX() > 0 || collAmnt.getY() > 0.0f || collAmnt.getZ() > 0.0f)
		{
			int dmgTaken = projectile->GetProjectileDmg();
			SpaceShipCurrentHealth -= dmgTaken;
			log << WARN << "Spaceship hit! It lost " << dmgTaken << ", " 
				<< SpaceShipCurrentHealth << "/" << SpaceShipMaxHealth <<"HP left" << std::endl;
				
			EmittProjectileHittParticles(*projectile);
				
			projectile->DestroyProjectile();
		}
	}
}

void SpaceShip::EmittProjectileHittParticles(Projectile& p)
{
	Vector3D origin = *p.transformable.getPosition();
	ParticleManager::Inst()->EmitStandardSpaceshipProjectileCollision(origin);
}
