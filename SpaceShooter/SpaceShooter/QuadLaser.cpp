#include "QuadLaser.h"


QuadLaser::QuadLaser()
	:Projectile(QUAD_LASER, 100.0f, 7.0f, 10, 0.3f, 0.2f)
{
}

QuadLaser::~QuadLaser()
{
}

void QuadLaser::FireProjectile( Transformable& ownerTransformable, GameObject* owner )
{
	Transformable frst(ownerTransformable);
	frst.SetPos(frst.getXPos()-0.5f, frst.getYPos()-0.5f, frst.getZPos());

	Transformable second(ownerTransformable);
	second.SetPos(second.getXPos()+0.5f, second.getYPos()+0.5f, second.getZPos());


	ProjectileManager::Inst()->Shoot(LASER_FAST, frst, owner);
	ProjectileManager::Inst()->Shoot(LASER_FAST, second, owner);
}

void QuadLaser::CreateProjectile( ProjectileTypes projectileType, std::string meshPathFromXmlFolder )
{

}
