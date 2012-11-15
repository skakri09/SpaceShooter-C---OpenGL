/********************************************************************
    created:    14:11:2012   23:38
    filename:   BasePowerup.h
    author:     Kristian Skarseth
    
    purpose:   A gameobject that spawns in the world with a colisionbox.
				If the player collides with it, he get access to the 
				projectile asociated with the object.
*********************************************************************/
#ifndef BasePowerup_h__
#define BasePowerup_h__

#include "GameObject.h"
#include "ProjectileTypes.h"
#include "VBODrawable.h"
#include "Texturable.h"
#include "Transformable.h"
#include "AABBCollisionBox.h"
#include "MeshFactory.h"
#include "CollisionTransformationInfo.h"

class WeaponUpgrade : public GameObject
{
public:
    WeaponUpgrade(ProjectileTypes thisType, 
		Vector3D startPos, 
		Vector3D targetPos,
		float velocity,
		float scale);

    ~WeaponUpgrade();

	virtual void Update(float deltaTime);
	
	virtual void Draw();

	Transformable transformable;
	VBODrawable vbo;
	Texturable texturable;
	AABBCollisionBox aabb;

	ProjectileTypes GetType(){return thisType;}

protected:
	ProjectileTypes thisType;

	std::string textureName;

	float rotation;

	Vector3D targetPos;

private:

	void CreateBox(ProjectileTypes projectileType);

};

#endif // BasePowerup_h__