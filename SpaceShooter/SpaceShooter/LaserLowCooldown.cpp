#include "LaserLowCooldown.h"

LaserLowCooldown::LaserLowCooldown() 
	:Projectile(LASER_FAST, 100.0f, 12.0f, 10, 0.2f, 0.03f)
{
	CreateProjectile(LASER_FAST,"..//3ds//Laser//Laser.3ds");
}

LaserLowCooldown::~LaserLowCooldown()
{

}

void LaserLowCooldown::CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder )
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

