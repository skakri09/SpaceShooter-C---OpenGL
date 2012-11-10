#include "TripleConeLaser.h"


TripleConeLaser::TripleConeLaser()
	:Projectile(TRIPLE_CONE_LASER, 100.0f, 7.0f, 10, 0.4f, 0.2f)
{

}

TripleConeLaser::~TripleConeLaser()
{
}

void TripleConeLaser::CreateProjectile( ProjectileTypes projectileType, std::string meshPathFromXmlFolder )
{
}
void TripleConeLaser::FireProjectile( Transformable& ownerTransformable, GameObject* owner )
{
	ProjectileManager::Inst()->Shoot(LASER_FAST, ownerTransformable, owner);
	
	Transformable left(ownerTransformable);
	left.SetDirectionVector(
		left.getDirectionVector().getX()-0.5f, 
		left.getDirectionVector().getY(),
		left.getDirectionVector().getZ());

	ProjectileManager::Inst()->Shoot(LASER_FAST, left, owner);

	Transformable right(ownerTransformable);
	right.SetDirectionVector(
		right.getDirectionVector().getX()+0.5f, 
		right.getDirectionVector().getY(),
		right.getDirectionVector().getZ());
	ProjectileManager::Inst()->Shoot(LASER_FAST, right, owner);
}
