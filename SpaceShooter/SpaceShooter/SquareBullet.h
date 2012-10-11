/********************************************************************
*	Created:	2012/09/10  19:16
*	Filename: 	SquareBullet.h
*	Author:		Kristian Skarseth
*	
*	purpose:	A simple square bullet. 6 sides. 
*********************************************************************/
#ifndef SquareBullet_h__
#define SquareBullet_h__

#include "Projectile.h"
#include "ProjectileFactory.h"

class SquareBullet : public Projectile
{
public:
	SquareBullet();
	virtual ~SquareBullet();

	void CreateDrawable();

private:

};

#endif // SimpleBullet_h__
