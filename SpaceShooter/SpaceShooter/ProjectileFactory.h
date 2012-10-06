/********************************************************************
*	Created:	2012/09/10  19:18
*	Filename: 	ProjectileFactory.h
*	Author:		Kristian Skarseth
*	
*	purpose:	A factory for projectiles. Returns a projectile class ready to
				be used as a projectile, based on the parameter in GetProjectile().

				When implementing a new projectile type, add a ProjectileType
				in the enum, create another vector with the bullettype (like
				the simpleBullets vector) and implement another function to 
				get the specific projectile (like the getSimpleBullet() func).
				Then add a case to the getProjectile switch, and you are done.
*********************************************************************/
#ifndef ProjectileFactory_h__
#define ProjectileFactory_h__

#include <map>
#include <vector>

#include "Projectile.h"
#include "SquareBullet.h"
#include "Logger.h"

enum ProjectileTypes {SIMPLE_BULLET};

class SquareBullet;

class ProjectileFactory
{
public:
	static ProjectileFactory* Inst();
	Projectile* GetProjectile(ProjectileTypes projectileType);
	
	
	void addDisplayList(ProjectileTypes projectileType, GLuint dispList);
	GLuint getDisplayList(ProjectileTypes projectileType);

protected:

private:
	Logger log;

	ProjectileFactory();
	~ProjectileFactory();
	
	SquareBullet* getSimpleBullet();
	
	std::vector<SquareBullet*> simpleBullets;

	std::map<ProjectileTypes, GLuint> displayLists;

};
#endif // ProjectileFactory_h__
