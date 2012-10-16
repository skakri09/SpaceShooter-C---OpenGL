#include "SquareFastBullet.h"

SquareFastBullet::SquareFastBullet() : Projectile(SQUARE_FAST_BULLET, 100.0f, 5.0f, 10, 0.2f, 1.0f, 1.0f, 1.0f)
{
	CreateGameObject();
}

SquareFastBullet::~SquareFastBullet()
{
}

void SquareFastBullet::CreateGameObject()
{
	MeshInfo* _meshInfo = ProjectileFactory::Inst()->GetMeshInfo(SQUARE_FAST_BULLET);

	if(_meshInfo == NULL)
	{	
		meshInfo = MeshFactory::Inst()->GetMesh("Mesh_SquareBullet.xml");
		collisionSphere = *meshInfo.collisionSphere;
		ProjectileFactory::Inst()->AddVBOInfo(SQUARE_FAST_BULLET, meshInfo);

	}	
	else
	{
		meshInfo = *_meshInfo;
		collisionSphere = *_meshInfo->collisionSphere;
	}
}


