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

#include "LaserLowCooldown.h"
#include "LaserHighCooldown.h"
#include "TripleConeLaser.h"
#include "ProjectileTypes.h"
#include "DoubleTripleConeLaser.h"
#include "DoubleLaser.h"
#include "QuadLaser.h"
#include "Logger.h"
#include "ManagerInterface.h"
#include "LaserWall.h"
#include "PlayerSeekingLaser.h"
#include "VBODrawable.h"

class ProjectileManager : public ManagerInterface
{
public:
	static ProjectileManager* Inst();    

	//A call to this should always be called before starting the game,
	//as it takes care of pre-loading the textures from disk. If they are not
	//pre-loaded, there will be a tiny freeze as they are loaded.
	void InitProjectileManager();

	void Update(float deltaTime);

	void DrawProjectiles();

	//Fires a specified projectile. 
	void Shoot(ProjectileTypes projectileType, Transformable& ownerTrans, GameObject* owner);

	//Returns the cooldown of the specified projectile type
	float GetProjectileCooldown(ProjectileTypes projectileType);

	//Returns meshinfo for the specified projectile type
	std::shared_ptr<MeshInfo> GetMeshInfo(ProjectileTypes projectileType);
	
	//Returns a pointer to the vector of Projectiles currently held by this 
	//manager.
	std::vector<std::shared_ptr<Projectile>>* GetProjectiles();

	void ResetProjectiles();

	void SetDrawAABB(bool renderAABB){this->renderAABB = renderAABB;}
	
private:
	ProjectileManager();
	~ProjectileManager();
	Logger log;

	VBODrawable laserVBO;

	bool renderAABB;
	//Map holding the cooldown for each projectile type
	std::map<ProjectileTypes, float> projectileCooldowns; 
	
	//Map holding the meshinfo for each projectile
	std::map<ProjectileTypes, std::shared_ptr<MeshInfo>> MeshInfos;

	//Returns a projectile object of the param type
	std::shared_ptr<Projectile> GetProjectile(ProjectileTypes projectileType);

	//Projectiles in use
	std::vector<std::shared_ptr<Projectile>> ActiveProjectiles;

	//All projectiles, used or none used
	std::vector<std::shared_ptr<Projectile>> projectiles;
};

#endif // ProjectileManager_h__