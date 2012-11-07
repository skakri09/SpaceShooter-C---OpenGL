#include "LaserLowCooldown.h"

LaserLowCooldown::LaserLowCooldown() 
	:Projectile(LASER_FAST, 100.0f, 7.0f, 10, 0.2f, 0.2f)
{
	CreateProjectile(LASER_FAST,"Mesh_Laser.xml");
}

LaserLowCooldown::~LaserLowCooldown()
{
}

void LaserLowCooldown::CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		MeshInfo* _meshInfo = ProjectileManager::Inst()->GetMeshInfo(projectileType);
		if(_meshInfo == NULL)
		{
			std::string meshPath = "..//xml//Projectiles//";
			meshPath += meshPathFromXmlFolder;
			MeshInfo meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

			vboDrawable.SetMeshInfo(meshInfo);
			collisionSphere = *meshInfo.collisionSphere;
		}
		else
		{
			vboDrawable.SetMeshInfo(*_meshInfo);
			collisionSphere = *_meshInfo->collisionSphere;
		}
	}
}
