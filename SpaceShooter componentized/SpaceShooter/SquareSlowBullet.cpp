#include "SquareSlowBullet.h"


SquareSlowBullet::SquareSlowBullet()
	:Projectile(SQUARE_SLOW_BULLET, 30.0f, 10.0f, 10, 1.5f, 1.0f)
{
	CreateProjectile(SQUARE_SLOW_BULLET, "Mesh_SquareBullet.xml");
}

SquareSlowBullet::~SquareSlowBullet()
{
}

void SquareSlowBullet::CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		MeshInfo* _meshInfo = ProjectileFactory::Inst()->GetMeshInfo(projectileType);
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
