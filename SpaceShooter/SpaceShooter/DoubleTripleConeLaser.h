/********************************************************************
    created:    10:11:2012   23:15
    filename:   DoubleTripleConeLaser.h
    author:     Kristian Skarseth
    
    purpose:    Shoots two lasers above eachother in 3 directions. 6 lasers total
*********************************************************************/
#ifndef DoubleTripleConeLaser_h__
#define DoubleTripleConeLaser_h__

#include "Projectile.h"
#include "ProjectileManager.h"

class DoubleTripleConeLaser : public Projectile
{
public:
    DoubleTripleConeLaser();
    ~DoubleTripleConeLaser();

	void FireProjectile(Transformable& ownerTransformable, GameObject* owner);

private:
	virtual void CreateProjectile(ProjectileTypes projectileType,  
		std::string meshPathFromXmlFolder );
};

#endif // DoubleTripleConeLaser_h__