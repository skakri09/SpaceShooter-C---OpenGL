#include "LaserHighCooldown.h"


LaserHighCooldown::LaserHighCooldown()
	:Projectile(LASER_SLOW, 30.0f, 10.0f, 10, 3.5f, 0.02f)
{
	CreateProjectile(LASER_SLOW, "..//3ds//Laser//Laser.3ds");
}

LaserHighCooldown::~LaserHighCooldown()
{
}

void LaserHighCooldown::CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::shared_ptr<MeshInfo> _meshInfo = ProjectileManager::Inst()->GetMeshInfo(projectileType);
		if(_meshInfo == NULL)
		{
			std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh(meshPathFromXmlFolder);

			vboDrawable.SetMeshInfo(meshInfo);
			collisionSphere = *meshInfo->collisionSphere;
		}
		else
		{
			vboDrawable.SetMeshInfo(_meshInfo);
			collisionSphere = *_meshInfo->collisionSphere;
		}
	}
}
