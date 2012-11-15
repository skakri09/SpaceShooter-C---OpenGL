#include "LaserWall.h"


LaserWall::LaserWall()
	:Projectile(LASER_WALL, 100.0f, 4.0f, 10, 0.4f, 0.2f)
{
}

LaserWall::~LaserWall()
{
}

void LaserWall::FireProjectile( Transformable& ownerTransformable, GameObject* owner )
{
	Transformable trans(ownerTransformable);
	for(float i = 0; i < 0.40; i+=0.04f)
	{
		trans.SetDirectionVector(trans.getDirectionVector().getX(), i, trans.getDirectionVector().getZ());
		ProjectileManager::Inst()->Shoot(LASER_FAST, trans, owner);
	}
	for(float i = 0; i > -0.40; i-=0.04f)
	{
		trans.SetDirectionVector(trans.getDirectionVector().getX(), i, trans.getDirectionVector().getZ());
		ProjectileManager::Inst()->Shoot(LASER_FAST, trans, owner);
	}
}

void LaserWall::CreateProjectile( ProjectileTypes projectileType, std::string meshPathFromXmlFolder )
{

}

