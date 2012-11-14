/********************************************************************
*	Created:	2012/09/07  10:20
*	Filename: 	Projectile.h
*	Author:		Kristian Skarseth
*	
*	purpose:	The class acts as a base class for any projectiles in the game.
*********************************************************************/
#ifndef Projectile_H
#define Projectile_H

#include "GameObject.h"
#include "Logger.h"
#include "MeshFactory.h"
#include "MeshXmlLoader.h"
#include "MeshInfo.h"
#include "ProjectileTypes.h"

#include "VBODrawable.h"
#include "Transformable.h"
#include "BoundingSphere.h"
#include "GameConstants.h"
#include "AABBCollisionBox.h"

class Projectile : public GameObject
{
public:
	Projectile( ProjectileTypes projectileType,
		float projectileeVelocity,
		float projectileFlytime, 
		int projectileDmg, 
		float projectileCooldown,
		float scale);

	virtual ~Projectile();

	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	virtual void FireProjectile(Transformable& ownerTransformable, GameObject* owner);

	bool isFired(){return fired;}

	void DestroyProjectile(){fired = false;}

	int GetProjectileDmg(){return projectileDamage;}

	float GetProjectileCooldown(){return projectileCooldown;}

	ProjectileTypes GetProjectileType(){return projectileType;}

	VBODrawable vboDrawable;		//A projectile is drawn with VBOs
	Transformable transformable;	//A projectile is transformable
	BoundingSphere collisionSphere;	//A projectile has a boundingSphere for collision
	AABBCollisionBox aabb;

protected:
	virtual void CreateProjectile(ProjectileTypes projectileType, std::string meshPathFromXmlFolder){}

	Vector3D initialStartPosition;
	float PROJECTILE_FLYTIME;
	float projectileCooldown;
	int projectileDamage;

	float projectileVelocity;
	float timeSinceFired;

	bool fired;
	float projectileSpeed;
	MeshXmlLoader meshLoader;

	ProjectileTypes projectileType;

	float scale;

private:
	Logger log;

};

#endif // Projectile_H
