/********************************************************************
*	Created:	2012/09/10  19:16
*	Filename: 	SquareFastBullet.h
*	Author:		Kristian Skarseth
*	
*	purpose:	A simple square bullet. 6 sides. 
*********************************************************************/
#ifndef SquareFastBullet_h__
#define SquareFastBullet_h__

#include "Projectile.h"
#include "ProjectileFactory.h"

class SquareFastBullet : public Projectile
{
public:
	SquareFastBullet();
	virtual ~SquareFastBullet();

	void CreateGameObject();

private:

};

#endif // SquareFastBullet_h__