/********************************************************************
    created:    11:10:2012   18:29
    filename:   ShooterModule.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ShooterModule_h__
#define ShooterModule_h__

#include "ProjectileFactory.h"
#include <deque>


class ShooterModule
{
public:
    ShooterModule();
    ~ShooterModule();

	//Fires a specified projectile. The startPos and startRotation is required
	//in order to fire the projectile from the correct position. 
	void Shoot(ProjectileTypes projectileType, Vector3D startPos, Vector3D directionVector);

	//Looping trough all the projectiles and updating them
	void UpdateModule(float deltaTime);
	
	//Looping trough all the projectiles and drawing them
	void DrawModule();

	std::deque<std::shared_ptr<Projectile>>* GetActiveProjectiles(){return &ActiveProjectiles;}
protected:

private:
	//using a deque as we're removing from the front of the container
	std::deque<std::shared_ptr<Projectile>> ActiveProjectiles;

	//Map holding the cooldown on the individual projectile types
	std::map<ProjectileTypes, float> projectileCooldowns;

};

#endif // ShooterModule_h__