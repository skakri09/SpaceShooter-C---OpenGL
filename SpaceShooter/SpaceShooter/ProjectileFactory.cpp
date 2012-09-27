#include "ProjectileFactory.h"	

CProjectileFactory::CProjectileFactory() : log("ProjectileFactory", WARN)
{
}
CProjectileFactory::~CProjectileFactory()
{

}
CProjectileFactory* CProjectileFactory::Inst()
{
	static CProjectileFactory* instance = new CProjectileFactory();
	return instance;
}

CProjectile* CProjectileFactory::GetProjectile( ProjectileTypes projectileType )
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

void CProjectileFactory::addDisplayList(ProjectileTypes projectileType, GLuint dispList )
{
	displayLists[projectileType] = dispList;
}

GLuint CProjectileFactory::getDisplayList( ProjectileTypes projectileType )
{
	if(displayLists.find(projectileType) != displayLists.end())
	{
		return displayLists.find(projectileType)->second;
	}
	else
	{
		log << INFO << "projectile display list was not found" << std::endl;
		return -1;
	}
}

CSquareBullet* CProjectileFactory::getSimpleBullet()
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

	simpleBullets.push_back(new CSquareBullet());
	return simpleBullets.back();
}

