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

void ProjectileFactory::addDisplayList(ProjectileTypes projectileType, GLuint dispList )
{
	displayLists[projectileType] = dispList;
}

GLuint ProjectileFactory::getDisplayList( ProjectileTypes projectileType )
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

