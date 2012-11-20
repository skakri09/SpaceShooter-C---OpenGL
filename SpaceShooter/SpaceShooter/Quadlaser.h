/********************************************************************
    created:    14:11:2012   23:04
    filename:   Quadlaser.h
    author:     Kristian Skarseth
    
    purpose:    Shoots 4 lasers straight forward
*********************************************************************/
#ifndef Quadlaser_h__
#define Quadlaser_h__

#include "Projectile.h"
#include "ProjectileManager.h"

class QuadLaser : public Projectile
{
public:
    QuadLaser();
    ~QuadLaser();

	void FireProjectile(Transformable& ownerTransformable, GameObject* owner);

private:
	virtual void CreateProjectile(ProjectileTypes projectileType,  
		std::string meshPathFromXmlFolder );


};

#endif // Quadlaser_h__