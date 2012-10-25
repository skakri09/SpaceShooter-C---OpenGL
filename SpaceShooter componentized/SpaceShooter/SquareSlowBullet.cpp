#include "SquareSlowBullet.h"


SquareSlowBullet::SquareSlowBullet()
	:Projectile(SQUARE_SLOW_BULLET, 75.0f, 10.0, 10, 1.0f, 1.0f, 1.0f, 1.0f)
{
	CreateGameObject();
}

SquareSlowBullet::~SquareSlowBullet()
{
}

void SquareSlowBullet::CreateGameObject()
{
	MeshInfo* _meshInfo = ProjectileFactory::Inst()->GetMeshInfo(SQUARE_SLOW_BULLET);

	if(_meshInfo == NULL)
	{	
		meshInfo = MeshFactory::Inst()->GetMesh("Mesh_SquareBullet.xml");
		collisionSphere = *meshInfo.collisionSphere;
		ProjectileFactory::Inst()->AddVBOInfo(SQUARE_SLOW_BULLET, meshInfo);
	}	
	else
	{
		meshInfo = *_meshInfo;
		collisionSphere = *_meshInfo->collisionSphere;
	}
}

	