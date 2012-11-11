#include "SpaceShip.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;
SpaceShip::SpaceShip(int spaceshipHP)
	:log("SpaceShipbase", WARN)
{
	this->SpaceShipMaxHealth = spaceshipHP;
	lives = 1;

	respawnImmunityDuration = 3.0f;
	respawnImmunityTimer = respawnImmunityDuration + 1.0f;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Update(float deltaTime)
{
	transformable.Update(deltaTime);
	collisionSphere.Update(transformable.GetCollisionTransformationInfo());
	shooterModule.UpdateModule(deltaTime);

	respawnImmunityTimer += deltaTime;
	if(respawnImmunityTimer <= respawnImmunityDuration)
	{

	}
	if(SpaceShipCurrentHealth <= 0)
	{
		lives -= 1;
		if(lives <= 0)
		{
			lives = 0;
			GameObject::FlagForKill();
		}
		else
		{
			Respawn();
		}
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
		std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

		vboDrawable.SetMeshInfo(meshInfo);
		collisionSphere = *meshInfo->collisionSphere;
	}
}

bool SpaceShip::Shoot(ProjectileTypes projectileType)
{
	return shooterModule.Shoot(projectileType, transformable, this);
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
	
	//Saving the init values in case we need to respawn later	
	respawnValues.dirVec = directionVec;
	respawnValues.rotAxis = rotationAxis;
	respawnValues.startPos = startPos;
	respawnValues.scale = scale;
	respawnValues.startRotDeg = startRotDeg;
}

void SpaceShip::HandleProjectileCollision( std::shared_ptr<Projectile> projectile )
{
	if(projectile->isFired())
	{
		BoundingSphere* projectileColSphere = &projectile->collisionSphere;

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

void SpaceShip::Respawn()
{
	transformable.Init(respawnValues.startPos, 
						respawnValues.rotAxis, 
						respawnValues.startRotDeg, 
						respawnValues.scale, 
						respawnValues.dirVec);

	SpaceShipCurrentHealth = SpaceShipMaxHealth;
	respawnImmunityTimer = 0.0f;
	log << WARN << "Respawned - " << SpaceShipCurrentHealth << " HP left - " << lives << " lives left." << std::endl;
}

