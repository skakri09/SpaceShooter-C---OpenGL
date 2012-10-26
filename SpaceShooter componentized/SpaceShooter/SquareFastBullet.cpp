#include "SquareFastBullet.h"

SquareFastBullet::SquareFastBullet() 
	:Projectile(SQUARE_SLOW_BULLET, 100.0f, 7.0f, 10, 0.2f, 1.0f)
{
	Projectile::CreateProjectile(SQUARE_FAST_BULLET,"Mesh_SquareBullet.xml");
}

SquareFastBullet::~SquareFastBullet()
{

}


