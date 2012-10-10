#include "ProjectileFactory.h"	

ProjectileFactory::ProjectileFactory() : log("ProjectileFactory", WARN)
{
}
ProjectileFactory::~ProjectileFactory()
{

}
ProjectileFactory* ProjectileFactory::Inst()
{
	static ProjectileFactory* instance = new ProjectileFactory();
	return instance;
}

Projectile* ProjectileFactory::GetProjectile( ProjectileTypes projectileType )
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

SquareBullet* ProjectileFactory::getSimpleBullet()
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

	simpleBullets.push_back(new SquareBullet());
	return simpleBullets.back();
}

