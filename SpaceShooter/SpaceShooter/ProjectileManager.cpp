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
	std::shared_ptr<Projectile> laserFast = GetProjectile(LASER_FAST);
	projectileCooldowns[LASER_FAST] = laserFast->GetProjectileCooldown();
	/***********************************************************************/

	std::shared_ptr<Projectile> laserSlow = GetProjectile(LASER_SLOW);
	projectileCooldowns[LASER_SLOW] = laserSlow->GetProjectileCooldown();

	std::shared_ptr<Projectile> tripleConeLaser = GetProjectile(TRIPLE_CONE_LASER);
	projectileCooldowns[TRIPLE_CONE_LASER] = tripleConeLaser->GetProjectileCooldown();

	std::shared_ptr<Projectile> dtripleConeLaser = GetProjectile(DOUBLE_TRIPLE_CONE_LASER);
	projectileCooldowns[DOUBLE_TRIPLE_CONE_LASER] = dtripleConeLaser->GetProjectileCooldown();
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
	glColor3f(1.0f, 0.7f, 0.0f);//orangeish color
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
	case LASER_FAST:
		projectiles.push_back(std::make_shared<LaserLowCooldown>());
		break;
	case LASER_SLOW:
		projectiles.push_back(std::make_shared<LaserHighCooldown>());
		break;
	case TRIPLE_CONE_LASER:
		projectiles.push_back(std::make_shared<TripleConeLaser>());
		break;
	case DOUBLE_TRIPLE_CONE_LASER:
		projectiles.push_back(std::make_shared<DoubleTripleConeLaser>());
		break;
	}

	return projectiles.back();
}

std::shared_ptr<MeshInfo> ProjectileManager::GetMeshInfo( ProjectileTypes projectileType )
{
	if(MeshInfos.find(projectileType) != MeshInfos.end())
	{
		return MeshInfos.find(projectileType)->second;
	}
	else
	{
		log << INFO << "projectile meshInfo was not found" << std::endl;
		return NULL;
	}
}

std::vector<std::shared_ptr<Projectile>>* ProjectileManager::GetProjectiles()
{
	return &ActiveProjectiles;
}
