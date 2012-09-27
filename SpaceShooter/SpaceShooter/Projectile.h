/********************************************************************
*	Created:	2012/09/07  10:20
*	Filename: 	Projectile.h
*	Author:		Kristian Skarseth
*	
*	purpose:	The class acts as a base class for any projectiles in the game.
				It has everything except the body of the projectile. 
*********************************************************************/
#ifndef Projectile_H
#define Projectile_H

#include "Drawable.h"
#include "Logger.h"

class CProjectile : public CDrawable
{
public:
	CProjectile(float projectileFlytime);
	~CProjectile();

	virtual void Draw(GLfloat deltaTime);

	virtual void FireProjectile(CVector3D startPos, CVector3D startRotation, GLfloat speed);

	bool isFired(){return fired;}

protected:
	float PROJECTILE_FLYTIME;
	
	float projectileVelocity;
	float timeSinceFired;
	CVector3D startRotation;
	CVector3D startPosition;
	bool fired;

private:
	Logger log;

};

#endif // Projectile_H
