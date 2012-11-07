/********************************************************************
*	Created:	2012/09/10  19:16
*	Filename: 	SquareFastBullet.h
*	Author:		Kristian Skarseth
*	
*	purpose:	A simple square bullet. 6 sides. 
*********************************************************************/
#ifndef SquareFastBullet_h__
#define SquareFastBullet_h__

#include "Projectile.h"
#include "ProjectileManager.h"
class LaserLowCooldown : public Projectile
{
public:
	LaserLowCooldown();
	~LaserLowCooldown();

protected:
	virtual void CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder );
};

#endif // SquareFastBullet_h__
