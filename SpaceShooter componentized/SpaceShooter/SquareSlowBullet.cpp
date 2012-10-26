#include "SquareSlowBullet.h"


SquareSlowBullet::SquareSlowBullet()
	:Projectile(SQUARE_SLOW_BULLET, 75.0f, 10.0f, 10, 1.0f, 1.0f)
{
	Projectile::CreateProjectile(SQUARE_SLOW_BULLET, "Mesh_SquareBullet.xml");
}

SquareSlowBullet::~SquareSlowBullet()
{
}

	