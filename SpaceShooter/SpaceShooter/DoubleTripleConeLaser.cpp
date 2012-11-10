#include "DoubleTripleConeLaser.h"


DoubleTripleConeLaser::DoubleTripleConeLaser()
	:Projectile(TRIPLE_CONE_LASER, 100.0f, 7.0f, 10, 0.4f, 0.2f)
{
}

DoubleTripleConeLaser::~DoubleTripleConeLaser()
{
}

void DoubleTripleConeLaser::CreateProjectile( ProjectileTypes projectileType, std::string meshPathFromXmlFolder )
{

}

void DoubleTripleConeLaser::FireProjectile( Transformable& ownerTransformable, GameObject* owner )
{
	ProjectileManager::Inst()->Shoot(TRIPLE_CONE_LASER, ownerTransformable, owner);

	Transformable second(ownerTransformable);
	second.SetPos(second.getXPos(), second.getYPos()+1, second.getZPos());

	ProjectileManager::Inst()->Shoot(TRIPLE_CONE_LASER, second, owner);
}
