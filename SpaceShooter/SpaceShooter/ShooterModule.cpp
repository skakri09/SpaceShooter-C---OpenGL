#include "ShooterModule.h"


ShooterModule::ShooterModule()
{
}

ShooterModule::~ShooterModule()
{
}

void ShooterModule::Shoot( ProjectileTypes projectileType, Transformable& ownerTransformable, GameObject* owner )
{
	float typeCD = ProjectileManager::Inst()->GetProjectileCooldown(projectileType);
	
	float projectileCD; 
	if(projectileCooldowns.find(projectileType) != projectileCooldowns.end())
	{
		projectileCD = projectileCooldowns.find(projectileType)->second;
	}
	else { projectileCD = 0.0f; }

	if(projectileCD <= 0.0f)
	{
		projectileCooldowns[projectileType] = typeCD;
		ProjectileManager::Inst()->Shoot(projectileType, ownerTransformable, owner);
	}
}

void ShooterModule::UpdateModule( float deltaTime )
{
	//Updating the cooldown on our projectiles types
	for(auto i = projectileCooldowns.begin(); i != projectileCooldowns.end(); i++)
	{
		(*i).second -= deltaTime;
	}
}
