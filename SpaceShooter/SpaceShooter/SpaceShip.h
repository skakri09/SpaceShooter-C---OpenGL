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

#include "Logger.h"
#include "GameObject.h"
#include "Projectile.h"
#include "MeshInfo.h"
#include "MeshXmlLoader.h"
#include "ShooterModule.h"

enum Axis {X_AXIS, Y_AXIS, Z_AXIS};

//Speed of the rotation around x, y and z axis
static const GLfloat ROTATE_SPEED = 200.0f;

//Used to store information about rotation around different axes
struct RotationInfo
{
	bool rotating;
	GLfloat currentAngle;
	GLfloat targetAngle;
};

class SpaceShip : public GameObject
{
public:
	SpaceShip(int spaceshipHP);

	virtual ~SpaceShip();

	virtual void Draw();

	//Stores a local deltaTime variable and updates
	//timeSinceLastFired. It's main functionality will
	//come from child classes overwriting, but be sure
	//that the child classes also call this Update function
	//to keep the time variables up to date
	virtual void Update(GLfloat deltaTime);
	
	//Will take care of initializing the spaceship by setting positions,
	//velocity etc and creating the VBO/displayList or whatever is being 
	//used for rendering.
	virtual void InitSpaceship(float startX, float startY, float startZ,
								float scaleX, float scaleY, float scaleZ,
								float startRotDeg, float rotX, float rotY, float rotZ,
								float dirVecX, float dirVecY, float dirVecZ);

	//Starts rotation around the specified axis
	void InitRotation(Axis axisToRotateArround);
	
	GLfloat getDeltaTime(){return deltaTime;}

	std::deque<std::shared_ptr<Projectile>>* GetProjectiles(){return shooterModule.GetActiveProjectiles();}

	void HandleProjectileCollision(std::deque<std::shared_ptr<Projectile>>* projectiles);

	int GetSpaceshipHP(){return SpaceShipCurrentHealth;}

protected:
	ShooterModule shooterModule;

	bool WasInited;

	virtual void CreateGameObject();

	virtual void DrawWithArrays();
	virtual void DrawWithIndices();

	int SpaceShipMaxHealth;
	int SpaceShipCurrentHealth;

	//Takes care of firing the spaceships gun.
	void FireGun();

	//handles the rotation arround the x, y and z axis
	void RotateArroundX(GLfloat deltaTime);
	void RotateArroundY(GLfloat deltaTime);
	void RotateArroundZ(GLfloat deltaTime);

	//Stores the current rotation in degrees around the 3 axes
	//Used to send as parameter to projectiles.
	//Vector3D rotation; 

	//Struct objects that hold rotation info about the differet axes
	RotationInfo xAxis;
	RotationInfo yAxis;
	RotationInfo zAxis;

	
private:
	Logger log;

	//local copy of deltaTime, used since we need to call the rotate functions
	//inside the Draw() function, and they need a deltaTime variable.
	GLfloat deltaTime; 
};

#endif // SpaceShip_H
