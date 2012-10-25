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
	virtual ~SquareSlowBullet();

	void CreateGameObject();

protected:

private:

};

#endif // SquareSlowBullet_h__
