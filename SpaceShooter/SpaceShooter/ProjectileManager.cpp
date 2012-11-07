#include "ProjectileManager.h"


ProjectileManager::ProjectileManager()
	:log("ProjectileManager", WARN)
{
}

ProjectileManager::~ProjectileManager()
{
}

ProjectileManager* ProjectileManager::Inst()
{
	static ProjectileManager* instance = new ProjectileManager();
	return instance;
}

void ProjectileManager::InitProjectileManager()
{
	//Repeat the two following lines of code for each ProjectileType added to the game!
	//This takes care of pre-loading the mesh into a VBO on the graphics card on startup
	//so we dont get a small freeze when trying to use an object that has not been loaded.
	/***********************************************************************/
	std::shared_ptr<Projectile> squarefast = GetProjectile(SQUARE_FAST_BULLET);
	projectileCooldowns[SQUARE_FAST_BULLET] = squarefast->GetProjectileCooldown();
	/***********************************************************************/

	std::shared_ptr<Projectile> squareslow = GetProjectile(SQUARE_SLOW_BULLET);
	projectileCooldowns[SQUARE_SLOW_BULLET] = squareslow->GetProjectileCooldown();
}

void ProjectileManager::Shoot( ProjectileTypes projectileType, Transformable& ownerTrans, GameObject* owner)
{
	std::shared_ptr<Projectile> projectile = GetProjectile(projectileType);
	projectile->FireProjectile(ownerTrans, owner);
	ActiveProjectiles.push_back(projectile);
}

float ProjectileManager::GetProjectileCooldown( ProjectileTypes projectileType )
{
	if(projectileCooldowns.find(projectileType) != projectileCooldowns.end())
	{
		return projectileCooldowns.find(projectileType)->second;
	}
	log << CRITICAL << "Cooldown for projectile type " << projectileType << " not found" << std::endl;
	return 0;
}

std::shared_ptr<Projectile> ProjectileManager::GetProjectile( ProjectileTypes projectileType )
{
	if(projectiles.size() > 0)
	{
		for(unsigned int i = 0; i < projectiles.size(); i++)
		{
			if(projectiles.at(i)->GetProjectileType() == projectileType)
			{
				if(!projectiles.at(i)->isFired())
				{
					return projectiles.at(i);
				}
			}
		}
	}
	switch(projectileType)
	{
	case SQUARE_FAST_BULLET:
		projectiles.push_back(std::make_shared<SquareFastBullet>());
		break;
	case SQUARE_SLOW_BULLET:
		projectiles.push_back(std::make_shared<SquareSlowBullet>());
		break;
	}

	return projectiles.back();
}

void ProjectileManager::AddVBOInfo( ProjectileTypes projectileType, MeshInfo meshInfo )
{
	MeshInfos[projectileType] = meshInfo;
}

MeshInfo* ProjectileManager::GetMeshInfo( ProjectileTypes projectileType )
{
	if(MeshInfos.find(projectileType) != MeshInfos.end())
	{
		return &MeshInfos.find(projectileType)->second;
	}
	else
	{
		log << INFO << "projectile meshInfo was not found" << std::endl;
		return NULL;
	}
}

void ProjectileManager::UpdateProjectiles(float deltaTime)
{
	//Updating the projectiles. Erasing them from the vector if 
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

void ProjectileManager::DrawProjectiles()
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

std::vector<std::shared_ptr<Projectile>>* ProjectileManager::GetProjectiles()
{
	return &ActiveProjectiles;
}


