/********************************************************************
    created:    7:10:2012   11:06
    filename:   SpaceShipManager.h
    author:     Kristian Skarseth
    
    purpose:    Manages all spaceships in the game, calling their update
				and draw functions, creating, initializing and destroying
				them.
*********************************************************************/
#ifndef SpaceShipManager_h__
#define SpaceShipManager_h__

#include "BaseEnemyShip.h"
#include "SithInfiltrator.h"
#include "ImperialTieFighter.h"
#include "ImperialTieInterceptor.h"
#include "PlayerSpaceShip.h"
#include "GameConstants.h"
#include "InputManager.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "GetRandomFloat.h"
#include "ImperialStarDestroyer.h"
#include "Planet.h"
class SpaceShipManager
{
public:
    SpaceShipManager();
    ~SpaceShipManager();

	//Initializing this manager. The input parameter
	//pointer should point to the inputManager used
	//by the game. We take it so that we can handle
	//input for the spaceship in this class.
	void InitManager(InputManager* input);
	
	//Calling Update() on all active spaceships
	void UpdateManager(GLfloat deltaTime);

	//Calling Draw() on all active spaceships
	void DrawSpaceShips();

private:
	Logger log;
	//locally stored pointer to the inputManager object
	//stored in gameManager, so that we can handle player
	//input internally instead of trough the gameManager
	InputManager* input;	

	PlayerSpaceShip player; // Player spaceship object

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

	void HandlePlayerRotation();

	std::vector<std::shared_ptr<BaseEnemyShip>> EnemySpaceShips;
	
	//Returns a random enemy
	std::shared_ptr<BaseEnemyShip> GetRandomEnemy();
	
	float TimeSinceLastEnemySpawn;

	Planet planet;
};

#endif // SpaceShipManager_h__