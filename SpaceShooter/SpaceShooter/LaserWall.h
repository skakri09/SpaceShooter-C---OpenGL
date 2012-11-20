/********************************************************************
    created:    15:11:2012   21:47
    filename:   LaserWall.h
    author:     Kristian Skarseth
    
    purpose:    A laser that spawns 20 lasers in a vertical cone
*********************************************************************/
#ifndef LaserWall_h__
#define LaserWall_h__

#include "ProjectileManager.h"
#include "Projectile.h"

class LaserWall : public Projectile
{
public:
    LaserWall();
    ~LaserWall();

	void FireProjectile(Transformable& ownerTransformable, GameObject* owner);

private:
	virtual void CreateProjectile(ProjectileTypes projectileType,  
		std::string meshPathFromXmlFolder );

};

#endif // LaserWall_h__