/********************************************************************
	created:	15:10:2012   9:27
	filename: 	SquareSlowBullet.h
	author:		Kristian Skarseth
	
	purpose:	A laser with high cooldown and low speed
*********************************************************************/
#ifndef SquareSlowBullet_h__
#define SquareSlowBullet_h__

#include "Projectile.h"
#include "ProjectileManager.h"

class LaserHighCooldown : public Projectile
{
public:
	LaserHighCooldown();
	~LaserHighCooldown();

protected:
	virtual void CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder );

private:

};

#endif // SquareSlowBullet_h__
