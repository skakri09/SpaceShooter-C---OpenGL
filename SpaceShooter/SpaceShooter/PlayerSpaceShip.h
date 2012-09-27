/********************************************************************
*	Created:	2012/09/10  19:42
*	Filename: 	PlayerSpaceShip.h
*	Author:		Kristian Skarseth
*	
*	purpose:	Space ship class for a player controller spaceship.
*********************************************************************/
#ifndef PlayerSpaceShip_H
#define PlayerSpaceShip_H

#include <vector>
#include "SpaceShipBase.h"
#include "Logger.h"
#include "Projectile.h"
#include "ProjectileFactory.h"

//Speed of the rotation arround x, y and z axis
static const GLfloat ROTATE_SPEED = 200.0f;

//CD on the spaceships fireing of projectiles in seconds
static const float FIRE_COOLDOWN  = 0.2f;

//Amount of time the projectiles fired by spaceship is visible in sec.
static const float PROJECTILE_FLYTIME = 5.0f;


enum Axis {X_AXIS, Y_AXIS, Z_AXIS};

//Used to store information about rotation arround different axes
struct RotationInfo
{
	bool rotating;
	GLfloat currentAngle;
	GLfloat targetAngle;
};

class CPlayerSpaceShip : public CSpaceShip
{
public:
	CPlayerSpaceShip(float startX, float startY, float startZ, float direction);
	~CPlayerSpaceShip();

	//Does drawing of the spaceship. Also takes care of updating position of the ship.
	void Draw(GLfloat deltaTime);

	//Creates the displaylist for the spaceship
	void CreateDrawable();

	//Starts rotation around the specified axis
	void InitRotation(Axis axisToRotateArround);

	//Takes care of firing the spaceships gun.
	void FireGun(float deltaTime);

private:
	Logger log;

	//Vector of projectiles, used to loop trough them and 
	//call their respecive Draw() function
	std::vector<CProjectile*> projectiles;
	void DrawProjectiles(float deltaTime);
	float timeSinceLastFired;
	
	//handles the rotation arround the x, y and z axis
	void RotateArroundX(GLfloat deltaTime);
	void RotateArroundY(GLfloat deltaTime);
	void RotateArroundZ(GLfloat deltaTime);
	
	//Stores the current rotation in degrees arround the 3 axes
	//Used to send as parameter to projectiles.
	CVector3D rotation; 

	//Struct objects that hold rotation info about the differet axes
	RotationInfo xAxis;
	RotationInfo yAxis;
	RotationInfo zAxis;
	
};


#endif // PlayerSpaceShip_H
