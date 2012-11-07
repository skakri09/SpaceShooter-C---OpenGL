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

//#include "Projectile.h"
#include "SquareFastBullet.h"
#include "Logger.h"
#include "ProjectileTypes.h"
#include "SquareSlowBullet.h"

class Projectile;
class ProjectileFactory
{
public:
	static ProjectileFactory* Inst();
	
	//Initializes the factory, loading all the different projectile
	//types and storing some key information for the various types.
	//This function should be called before or when starting a new 
	//game so we dont end up having to load resources when firing
	//the first shot!
	//Note: This force-loads all projectile types. If we at a later point
	//end up with a lot of different projectile types that are not all unlocked
	//at once, we should change the force-loading of all projectile types to be
	//based on the types we have unlocked.
	void InitProjectileFactory();
	
	std::shared_ptr<Projectile> GetProjectile(ProjectileTypes projectileType);

	void AddVBOInfo(ProjectileTypes projectileType, MeshInfo meshInfo);
	
	MeshInfo* GetMeshInfo(ProjectileTypes projectileType);

	float GetProjectileCooldown(ProjectileTypes projectileType);
protected:

private:
	Logger log;
	bool wasInited;
	ProjectileFactory();
	~ProjectileFactory();
	
	std::map<ProjectileTypes, float> projectileCooldowns; 

	
	
	std::vector<std::shared_ptr<Projectile>> projectiles;

	std::map<ProjectileTypes, MeshInfo> MeshInfos;

};


#endif // ProjectileFactory_h__
