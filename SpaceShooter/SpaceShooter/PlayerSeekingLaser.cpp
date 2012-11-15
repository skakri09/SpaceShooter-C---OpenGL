#include "PlayerSeekingLaser.h"
#include "SpaceShipManager.h"

PlayerSeekingLaser::PlayerSeekingLaser()
	: Projectile(PLAYER_SEEKING_LASER, 500.0f, 4.0f, 10, 1.0f, 0.2f)
{
	CreateProjectile(PLAYER_SEEKING_LASER,"..//3ds//Laser//Laser.3ds");
}

PlayerSeekingLaser::~PlayerSeekingLaser()
{
	
}

void PlayerSeekingLaser::FireProjectile( Transformable& ownerTransformable, GameObject* owner )
{
	Vector3D* Ppos = SpaceShipManager::Inst()->GetPlayer()->transformable.getPosition();
	Vector3D velocity = *Ppos - *ownerTransformable.getPosition();
	velocity.Normalize();
	Vector3D dirVec = velocity;
	velocity*=projectileVelocity;
	
	SetOwner(owner);
	Vector3D axis;
	float foo = dirVec.getX();

	if(ownerTransformable.getDirectionVector().getX() < 0.0f)
	{
		if(dirVec.getZ()>0)
			axis.setValues(0.0f, 45.0f*foo, 0.0f);
		else axis.setValues(0.0f, -45.0f*foo, 0.0f);

		transformable.Init(*ownerTransformable.getPosition(), axis, 1,
			dirVec);
	}
	else if(dirVec.getX() > 0.0f)
	{
		if(dirVec.getZ()>0)
			axis.setValues(0.0f, 45.0f*foo, 0.0f);
		else axis.setValues(0.0f, -45.0f*foo, 0.0f);
		transformable.Init(*ownerTransformable.getPosition(), axis, 1,
			dirVec);
	}
	else
	{
		transformable.Init(*ownerTransformable.getPosition(), Vector3D::ZeroVec(), 1,
			dirVec);
	}

	transformable.SetScale(scale, scale, scale);
	timeSinceFired = 0.0f;

	velocity.Normalize();
	velocity*=projectileVelocity;
	transformable.SetVelocity(velocity);

	initialStartPosition = *ownerTransformable.getPosition();

	collisionSphere.Update(transformable.GetCollisionTransformationInfo());
	aabb.Update(transformable.GetCollisionTransformationInfo());

	fired = true;
	//ProjectileManager::Inst()->Shoot(PLAYER_SEEKING_LASER, trans, owner);
}

void PlayerSeekingLaser::CreateProjectile( ProjectileTypes projectileType, std::string meshPathFromXmlFolder )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::shared_ptr<MeshInfo> _meshInfo = ProjectileManager::Inst()->GetMeshInfo(projectileType);
		if(_meshInfo == NULL)
		{
			std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh(meshPathFromXmlFolder);

			vboDrawable.SetMeshInfo(meshInfo);
			collisionSphere = *meshInfo->collisionSphere;
			aabb = *meshInfo->aabb;
		}
		else
		{
			vboDrawable.SetMeshInfo(_meshInfo);
			collisionSphere = *_meshInfo->collisionSphere;
			aabb = *_meshInfo->aabb;
		}
	}
}

