#include "ProjectileFactory.h"	

ProjectileFactory::ProjectileFactory() : log("ProjectileFactory", WARN)
{
	wasInited = false;
}
ProjectileFactory::~ProjectileFactory()
{

}
ProjectileFactory* ProjectileFactory::Inst()
{
	static ProjectileFactory* instance = new ProjectileFactory();
	return instance;
}

void ProjectileFactory::AddVBOInfo(ProjectileTypes projectileType, MeshInfo meshInfo)
{
	MeshInfos[projectileType] = meshInfo;
}

MeshInfo* ProjectileFactory::GetMeshInfo( ProjectileTypes projectileType )
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

std::shared_ptr<Projectile> ProjectileFactory::GetProjectile(ProjectileTypes projectileType)
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

float ProjectileFactory::GetProjectileCooldown( ProjectileTypes projectileType )
{
	if(projectileCooldowns.find(projectileType) != projectileCooldowns.end())
	{
		return projectileCooldowns.find(projectileType)->second;
	}
	log << CRITICAL << "Cooldown for projectile type " << projectileType << " not found" << std::endl;
	return 0;
}

void ProjectileFactory::InitProjectileFactory()
{
	wasInited = true;

//Repeat the two following lines of code for each ProjectileType added to the game!
	/***********************************************************************/
	std::shared_ptr<Projectile> squarefast = GetProjectile(SQUARE_FAST_BULLET);
	projectileCooldowns[SQUARE_FAST_BULLET] = squarefast->GetProjectileCooldown();

	std::shared_ptr<Projectile> squareslow = GetProjectile(SQUARE_SLOW_BULLET);
	projectileCooldowns[SQUARE_SLOW_BULLET] = squareslow->GetProjectileCooldown();
	/***********************************************************************/
}

