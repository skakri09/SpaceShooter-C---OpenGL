/********************************************************************
    created:    11:10:2012   18:29
    filename:   ShooterModule.h
    author:     Kristian Skarseth
    
    purpose:    A module that gives a spaceship the ability to shoot
*********************************************************************/
#ifndef ShooterModule_h__
#define ShooterModule_h__

#include <vector>
#include <map>

#include <gl/glew.h>

#include "GameObject.h"
#include "ShooterModule.h"
#include "ProjectileTypes.h"
#include "Transformable.h"
#include "Projectile.h"
#include "ProjectileManager.h"

class ShooterModule
{
public:
    ShooterModule();
    ~ShooterModule();

	//Fires a specified projectile. The startPos and startRotation is required
	//in order to fire the projectile from the correct position. 
	void Shoot(ProjectileTypes projectileType, Transformable& ownerTransformable, GameObject* owner);

	//Looping trough all the projectiles and updating them
	void UpdateModule(float deltaTime);
	

private:
	//Map holding the cooldown on the individual projectile types
	std::map<ProjectileTypes, float> projectileCooldowns;

};

#endif // ShooterModule_h__