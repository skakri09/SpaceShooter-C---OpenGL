/********************************************************************
    created:    7:10:2012   11:06
    filename:   SpaceShipManager.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SpaceShipManager_h__
#define SpaceShipManager_h__

#include "SimpleEnemyShip.h"
#include "PlayerSpaceShip.h"
#include "GameConstants.h"
#include "InputManager.h"
#include "Logger.h"

class SpaceShipManager
{
public:
    SpaceShipManager();
    ~SpaceShipManager();

	void InitManager(InputManager* input);
	
	void UpdateManager(GLfloat deltaTime);

	void DrawSpaceShips();

protected:

private:
	Logger log;
	//locally stored pointer to the inputManager object
	//stored in gameManager, so that we can handle player
	//input internally instead of trough the gameManager
	InputManager* input;	

	PlayerSpaceShip player; // Player spaceship object
	SimpleEnemyShip enemy;  // Enemy spaceship object

	//Handles movement along the x axis. Checks for input and changes
	//x velocity based on the input.
	void HandleXAxisMovement();

	//Handles movement along the y axis. Checks for input and changes
	//y velocity based on the input.
	void HandleYAxisMovement();

	//Does simple collision checking with the frustum. The truth is it
	//only checks for collision against set x and y coordinates that 
	//matches the sides of the screen where the ship starts. If its
	//moved somewhere along the z axis, it wont check against the 
	//frustum, but against an invisible wall matching the coordinates.
	//This is because we use a perspective projection instead of a
	//orthographic projection
	void HandleFrustumCollision();
};

#endif // SpaceShipManager_h__