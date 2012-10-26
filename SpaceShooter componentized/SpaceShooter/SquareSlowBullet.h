/********************************************************************
	created:	15:10:2012   9:27
	filename: 	SquareSlowBullet.h
	author:		Kristian Skarseth
	
	purpose:	A slow square bullet
*********************************************************************/
#ifndef SquareSlowBullet_h__
#define SquareSlowBullet_h__

#include "Projectile.h"
#include "ProjectileFactory.h"

class SquareSlowBullet : public Projectile
{
public:
	SquareSlowBullet();
	~SquareSlowBullet();

protected:
	//void CreateProjectile(ProjectileTypes projectileType, std::string meshPathFromXmlFolder);
	virtual void CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder );

private:

};

#endif // SquareSlowBullet_h__
