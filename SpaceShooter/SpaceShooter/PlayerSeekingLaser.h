/********************************************************************
    created:    15:11:2012   22:54
    filename:   PlayerSeekingLaser.h
    author:     Kristian Skarseth
    
    purpose:    A laser that targets the player when fired. It goes straight
				ahead, but towards the position the player was when fired.
*********************************************************************/
#ifndef PlayerSeekingLaser_h__
#define PlayerSeekingLaser_h__

#include "Projectile.h"
#include "ProjectileManager.h"


class PlayerSeekingLaser : public Projectile
{
public:
    PlayerSeekingLaser();
    ~PlayerSeekingLaser();

	void FireProjectile(Transformable& ownerTransformable, GameObject* owner);

private:
	virtual void CreateProjectile(ProjectileTypes projectileType,  
		std::string meshPathFromXmlFolder );

};

#endif // PlayerSeekingLaser_h__