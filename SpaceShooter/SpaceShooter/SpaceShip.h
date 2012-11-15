/********************************************************************
*	Created:	2012/09/06  10:04
*	Filename: 	SpaceShip.h
*	Author:		Kristian Skarseth
*	
*	purpose:	Base class for any spaceship, enemy or player.
*********************************************************************/

#ifndef SpaceShip_H
#define SpaceShip_H

#include <vector>
#include <memory>

#include "Logger.h"
#include "GameObject.h"
#include "Projectile.h"
#include "MeshInfo.h"
#include "MeshXmlLoader.h"
#include "ParticleManager.h"

//Components
#include "ShooterModule.h"
#include "VBODrawable.h"
#include "Transformable.h"
#include "AABBCollisionBox.h"

enum Axis {X_AXIS, Y_AXIS, Z_AXIS};

//Speed of the rotation around x, y and z axis
static const GLfloat ROTATE_SPEED = 200.0f;

struct RespawnValues
{
	Vector3D startPos;
	Vector3D rotation;
	Vector3D dirVec;
	float scale;
};

class SpaceShip : public GameObject
{
public:
	SpaceShip(int spaceshipHP);

	virtual ~SpaceShip();

	virtual void Update(float deltaTime);
	
	virtual void Draw();
	
	
	//Will take care of initializing the spaceship by setting positions,
	//velocity etc and creating the VBO/displayList or whatever is being 
	//used for rendering.
	virtual void InitSpaceShip(float startX, float startY, float startZ,
								float startRotDeg, float rotX, float rotY, float rotZ,
								float dirVecX, float dirVecY, float dirVecZ,
								float scale);

	void HandleProjectileCollision(std::shared_ptr<Projectile> projectile);

	int GetSpaceshipHP(){return SpaceShipCurrentHealth;}
	int GetSpaceshipMaxHP(){return SpaceShipMaxHealth;}

	unsigned int GetLives(){return lives;}

	ShooterModule shooterModule;	//A spaceship can shoot
	VBODrawable vboDrawable;		//A spaceship is drawn with VBOs
	Transformable transformable;	//A spaceship is transformable
	AABBCollisionBox aabb;			//A spaceship has an AABB for collisio

	//Takes care of firing the spaceships gun.
	bool Shoot(ProjectileTypes projectileType);

protected:
	virtual void CreateGameObject(std::string meshPathFrom3dsFolder);

	unsigned int lives;			//Amnt of times the spaceship can die
	int SpaceShipMaxHealth;		//Max health of the ship
	int SpaceShipCurrentHealth;	//Current health of the ship

	void EmittProjectileHittParticles(Projectile& p);

	void Respawn();

	RespawnValues respawnValues;
	float respawnImmunityTimer;
	float respawnImmunityDuration;

private:
	Logger log;

};

#endif // SpaceShip_H
