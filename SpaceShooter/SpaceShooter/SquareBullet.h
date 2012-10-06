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

static const float PROJECTILE_VELOCITY = -80.0f;

class SquareBullet : public Projectile
{
public:
	SquareBullet();
	~SquareBullet();

	void CreateDrawable();

};

#endif // SimpleBullet_h__
