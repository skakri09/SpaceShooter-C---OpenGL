#include "SquareFastBullet.h"

SquareFastBullet::SquareFastBullet() 
	:Projectile(SQUARE_SLOW_BULLET, 100.0f, 7.0f, 10, 0.2f, 1.0f)
{
	Projectile::CreateProjectile(SQUARE_FAST_BULLET,"Mesh_SquareBullet.xml");
}

SquareFastBullet::~SquareFastBullet()
{

}

void SquareFastBullet::CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder )
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
