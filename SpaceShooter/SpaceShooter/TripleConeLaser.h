/********************************************************************
    created:    10:11:2012   22:37
    filename:   TripleConeLaser.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef TripleConeLaser_h__
#define TripleConeLaser_h__

#include "Projectile.h"
#include "ProjectileManager.h"

class TripleConeLaser : public Projectile
{
public:
    TripleConeLaser();
    ~TripleConeLaser();

	void FireProjectile(Transformable& ownerTransformable, GameObject* owner);

private:
	virtual void CreateProjectile(ProjectileTypes projectileType,  
		std::string meshPathFromXmlFolder );
};

#endif // TripleConeLaser_h__