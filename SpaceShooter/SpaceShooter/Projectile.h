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

class Projectile : public Drawable
{
public:
	Projectile(float projectileFlytime);
	virtual ~Projectile();

	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	virtual void FireProjectile(Vector3D startPos, Vector3D startRotation, GLfloat speed);

	bool isFired(){return fired;}

protected:
	float PROJECTILE_FLYTIME;
	
	float projectileVelocity;
	float timeSinceFired;
	Vector3D startRotation;
	Vector3D startPosition;
	bool fired;

private:
	Logger log;

};

#endif // Projectile_H
