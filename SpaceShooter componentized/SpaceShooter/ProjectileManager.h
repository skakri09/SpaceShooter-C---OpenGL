/********************************************************************
    created:    6:11:2012   18:18
    filename:   ProjectileManager.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ProjectileManager_h__
#define ProjectileManager_h__

#include <memory>
#include <map>


#include "SquareFastBullet.h"
#include "SquareSlowBullet.h"
#include "ProjectileTypes.h"
#include "Logger.h"

class ProjectileManager
{
public:
	static ProjectileManager* Inst();    

	void InitProjectileManager();

	void UpdateProjectiles(float deltaTime);

	void DrawProjectiles();

	//Fires a specified projectile. 
	void Shoot(ProjectileTypes projectileType, Transformable& ownerTrans, GameObject* owner);

	float GetProjectileCooldown(ProjectileTypes projectileType);

	MeshInfo* GetMeshInfo(ProjectileTypes projectileType);
	
	std::vector<std::shared_ptr<Projectile>>* GetProjectiles();
private:
	ProjectileManager();
	~ProjectileManager();
	Logger log;

	//Map holding the cooldown for each projectile type
	std::map<ProjectileTypes, float> projectileCooldowns; 
	
	//Map holding the meshinfo for each projectile
	std::map<ProjectileTypes, MeshInfo> MeshInfos;

	std::shared_ptr<Projectile> GetProjectile(ProjectileTypes projectileType);

	void AddVBOInfo(ProjectileTypes projectileType, MeshInfo meshInfo);

	//Projectiles in use
	std::vector<std::shared_ptr<Projectile>> ActiveProjectiles;

	//All projectiles, used or none used
	std::vector<std::shared_ptr<Projectile>> projectiles;
};

#endif // ProjectileManager_h__