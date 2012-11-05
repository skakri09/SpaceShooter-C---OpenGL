/********************************************************************
*	Created:	2012/09/06  10:04
*	Filename: 	SpaceShip.h
*	Author:		Kristian Skarseth
*	
*	purpose:	Base class for any spaceship, enemy or player.
				Contains functionality to draw and set/get position and
				velocity of the spaceship.

				Position and velocity comes in form of a Vector3D, and the
				Draw() function is inherited from the Drawable abstract class 
				which works as an interface in this case.
*********************************************************************/

#ifndef SpaceShip_H
#define SpaceShip_H

#include <vector>

#include "Logger.h"
#include "GameObject.h"
#include "Projectile.h"
#include "MeshInfo.h"
#include "MeshXmlLoader.h"

//Components
#include "ShooterModule.h"
#include "VBODrawable.h"
#include "Transformable.h"
#include "BoundingSphere.h"
#include "ParticleEmitter.h"

enum Axis {X_AXIS, Y_AXIS, Z_AXIS};

//Speed of the rotation around x, y and z axis
static const GLfloat ROTATE_SPEED = 200.0f;



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

	//Starts rotation around the specified axis
	//void InitRotation(Axis axisToRotateArround);

	std::vector<std::shared_ptr<Projectile>>* GetProjectiles(){return shooterModule.GetActiveProjectiles();}

	void HandleProjectileCollision(std::vector<std::shared_ptr<Projectile>>* projectiles);

	int GetSpaceshipHP(){return SpaceShipCurrentHealth;}
	
	ShooterModule shooterModule;	//A spaceship can shoot
	VBODrawable vboDrawable;		//A spaceship is drawn with VBOs
	Transformable transformable;	//A spaceship is transformable
	BoundingSphere collisionSphere;	//A spaceship has a boundingSphere for collision
	ParticleEmitter particleEmitter;//A spaceship can emitt particles

protected:
	
	virtual void CreateGameObject(std::string meshPathFrom3dsFolder);


	int SpaceShipMaxHealth;
	int SpaceShipCurrentHealth;

	//Takes care of firing the spaceships gun.
	void FireGun(ProjectileTypes projectileType);

	void EmittProjectileHittParticles(Projectile& p);

private:
	Logger log;

};

#endif // SpaceShip_H
