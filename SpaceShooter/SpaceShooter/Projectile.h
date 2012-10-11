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

#include "GameObject.h"
#include "Logger.h"
#include "MeshLoader.h"
#include "Mesh.h"

class Projectile : public GameObject
{
public:
	Projectile(float projectileFlytime, int projectileDmg);
	virtual ~Projectile();

	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	virtual void FireProjectile(Vector3D startPos, Vector3D startRotation, Vector3D scale, GLfloat speed);

	bool isFired(){return fired;}

	void DestroyProjectile(){fired = false;}

	int GetProjectileDmg(){return projectileDamage;}

protected:
	float PROJECTILE_FLYTIME;
	
	int projectileDamage;

	float projectileVelocity;
	float timeSinceFired;
	Vector3D startRotation;
	Vector3D startPosition;
	bool fired;

	MeshLoader meshLoader;

	virtual void UpdateTransformationValues();

private:
	Logger log;

};

#endif // Projectile_H
