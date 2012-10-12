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
#include "MeshXmlLoader.h"
#include "Mesh.h"

class Projectile : public GameObject
{
public:
	Projectile(	float projectileFlytime, 
				int projectileDmg, 
				float projectileCooldown,
				float scaleX, float scaleY, float scaleZ);
	virtual ~Projectile();

	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	virtual void FireProjectile(Vector3D startPos, Vector3D directionVector);

	bool isFired(){return fired;}

	void DestroyProjectile(){fired = false;}

	int GetProjectileDmg(){return projectileDamage;}

	float GetProjectileCooldown(){return projectileCooldown;}

protected:
	float PROJECTILE_FLYTIME;
	float projectileCooldown;
	int projectileDamage;

	float projectileVelocity;
	float timeSinceFired;
	Vector3D objectRotation;
	Vector3D startPosition;
	bool fired;
	float projectileSpeed;
	MeshXmlLoader meshLoader;

	virtual void UpdateTransformationValues();

private:
	Logger log;

};

#endif // Projectile_H
