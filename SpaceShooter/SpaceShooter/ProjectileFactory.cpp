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

std::shared_ptr<Projectile> ProjectileFactory::GetProjectile( ProjectileTypes projectileType )
{
	switch(projectileType)
	{
	case SIMPLE_BULLET:
		return getSimpleBullet();
		break;
	}
	log << WARN << "GetProjectile() did not find anything to return, returning NULL" << std::endl;
	return NULL;
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

std::shared_ptr<SquareBullet> ProjectileFactory::getSimpleBullet()
{
	if(simpleBullets.size() > 0)
	{
		for(unsigned int i = 0; i < simpleBullets.size(); i++)
		{
			if(!simpleBullets.at(i)->isFired())
			{
				return simpleBullets.at(i);
			}
		}
	}

	simpleBullets.push_back(std::make_shared<SquareBullet>());
	return simpleBullets.back();
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
	std::shared_ptr<Projectile> dummyPtr = GetProjectile(SIMPLE_BULLET);
	projectileCooldowns[SIMPLE_BULLET] = dummyPtr->GetProjectileCooldown();
	/***********************************************************************/
}

