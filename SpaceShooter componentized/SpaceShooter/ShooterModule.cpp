#include "ShooterModule.h"


ShooterModule::ShooterModule()
{
}

ShooterModule::~ShooterModule()
{
}

void ShooterModule::Shoot( ProjectileTypes projectileType, Transformable& ownerTransformable )
{
	float typeCD = ProjectileFactory::Inst()->GetProjectileCooldown(projectileType);
	
	float projectileCD; 
	if(projectileCooldowns.find(projectileType) != projectileCooldowns.end())
	{
		projectileCD = projectileCooldowns.find(projectileType)->second;
	}
	else { projectileCD = 0.0f; }

	if(projectileCD <= 0.0f)
	{
		projectileCooldowns[projectileType] = typeCD;
		std::shared_ptr<Projectile> projectile = ProjectileFactory::Inst()->GetProjectile(projectileType);
		projectile->FireProjectile(ownerTransformable);
		ActiveProjectiles.push_back(projectile);
	}
}

void ShooterModule::UpdateModule( float deltaTime )
{
	//Updating the cooldown on our projectiles types
	for(auto i = projectileCooldowns.begin(); i != projectileCooldowns.end(); i++)
	{
		(*i).second -= deltaTime;
	}
	
	//Updating the projectiles. Erasing them from the deque if 
	//they are no longer tagged as "fired"
	for(auto i = ActiveProjectiles.begin(); i != ActiveProjectiles.end();)
	{
		if( !(*i)->isFired() )
		{
			i = ActiveProjectiles.erase(i);
		}
		else
		{
			(*i)->Update(deltaTime);
			++i;
		}
	}
}

void ShooterModule::DrawModule()
{
	glPushMatrix();
	//Drawing all our projectiles if they are tagged as "fired"
	glColor3f(1.0f, 0.5f, 0.0f);
	for(auto i = ActiveProjectiles.begin(); i != ActiveProjectiles.end(); i++)
	{
		if( (*i)->isFired() )
		{
			(*i)->Draw();
		}
	}
	glColor3f(1.0, 1.0f, 1.0f);
	glPopMatrix();
}
