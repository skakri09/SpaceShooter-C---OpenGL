/********************************************************************
    created:    14:11:2012   22:43
    filename:   DoubleLaser.h
    author:     Kristian Skarseth
    
    purpose:    Shoots two lasers straight forward
*********************************************************************/
#ifndef DoubleLaser_h__
#define DoubleLaser_h__

#include "ProjectileManager.h"
#include "Projectile.h"

class DoubleLaser : public Projectile
{
public:
    DoubleLaser();
    ~DoubleLaser();
	
	void FireProjectile(Transformable& ownerTransformable, GameObject* owner);

private:
	virtual void CreateProjectile(ProjectileTypes projectileType,  
		std::string meshPathFromXmlFolder );

};

#endif // DoubleLaser_h__