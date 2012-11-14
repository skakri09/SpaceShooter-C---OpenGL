#include "DoubleLaser.h"


DoubleLaser::DoubleLaser()
	:Projectile(DOUBLE_LASER, 100.0f, 7.0f, 10, 0.3f, 0.2f)
{
}

DoubleLaser::~DoubleLaser()
{
}

void DoubleLaser::FireProjectile( Transformable& ownerTransformable, GameObject* owner )
{
	Transformable frst(ownerTransformable);
	frst.SetPos(frst.getXPos()-0.5f, frst.getYPos(), frst.getZPos());

	Transformable second(ownerTransformable);
	second.SetPos(second.getXPos()+0.5f, second.getYPos(), second.getZPos());


	ProjectileManager::Inst()->Shoot(LASER_FAST, frst, owner);
	ProjectileManager::Inst()->Shoot(LASER_FAST, second, owner);
}

void DoubleLaser::CreateProjectile( ProjectileTypes projectileType, std::string meshPathFromXmlFolder )
{
}

