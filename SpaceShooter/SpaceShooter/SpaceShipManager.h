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
#include "ImperialTieFighter.h"
#include "ImperialTieInterceptor.h"
#include "PlayerSpaceShip.h"
#include "GameConstants.h"
#include "InputManager.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "GetRandomFloat.h"
#include "ImperialStarDestroyer.h"
#include "ProjectileManager.h"
#include "GameState.h"
#include "ManagerInterface.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "WeaponUpgrade.h"
#include "Texturable.h"
#include "ImperialShuttle.h"

class SpaceShipManager : public ManagerInterface
{
public:
	static SpaceShipManager* Inst();

	//Initializing this manager. The input parameter
	//pointer should point to the inputManager used
	//by the game. We take it so that we can handle
	//input for the spaceship in this class.
	void InitManager(InputManager* input, GameState* gameState, ScoreManager* scoreManager);
	
	//Calling Update() on all active spaceships
	void Update(GLfloat deltaTime);

	//Calling Draw() on all active spaceships
	void DrawSpaceShips();

	void TransferShipToShipManager(std::shared_ptr<BaseEnemyShip> ship);
	void TransferShipToShipManager(std::shared_ptr<PlayerSpaceShip> ship);

	std::shared_ptr<PlayerSpaceShip> GetPlayer();

	std::vector<std::shared_ptr<BaseEnemyShip>>* GetEnemySpaceships();

	void ResetSpaceships();
	
	void SetDrawAABB(bool drawAABB){drawAABBs = drawAABB;}
	bool IsDrawingAABB(){return drawAABBs;}

	void SpawnProjectilePowerup(ProjectileTypes typeToSpawn, Vector3D* startPos );

private:
	Logger log;

	SpaceShipManager();
	~SpaceShipManager();

	Texturable tex;

	bool drawAABBs;
	//locally stored pointer to the inputManager object
	//stored in GamePlayManager, so that we can handle player
	//input internally instead of trough the GamePlayManager
	InputManager* input;	

	//Local pointer to the gameState so we can switch to another state when player dies
	GameState* gameState;

	//Local pointer to scoremanager so we can notify it when the player kills something
	ScoreManager* scoreManager;

	std::shared_ptr<PlayerSpaceShip> player; // Player spaceship object

	//Handles movement along the x axis. Checks for input and changes
	//x velocity based on the input.
	void HandleXAxisMovement();

	//Handles movement along the y axis. Checks for input and changes
	//y velocity based on the input.
	void HandleYAxisMovement();

	//Checks for input that changes the players weapon selection
	void UpdatePlayerWeaponSelection();

	//Does simple collision checking with the frustum. The truth is it
	//only checks for collision against set x and y coordinates that 
	//matches the sides of the screen where the ship starts. If its
	//moved somewhere along the z axis, it wont check against the 
	//frustum, but against an invisible wall matching the coordinates.
	//This is because we use a perspective projection instead of a
	//orthographic projection
	void HandleFrustumCollision();

	void HandleCollision();

	void UpdateEnemies(float deltaTime);

	void UpdateWepUpgrades(float deltaTime);

	void HandlePlayerInput();

	std::vector<std::shared_ptr<BaseEnemyShip>> EnemySpaceShips;
	std::vector<std::shared_ptr<BaseEnemyShip>> EnemyShipsForTransfer;
	std::vector<std::shared_ptr<WeaponUpgrade>> wepUpgrades;

	void SpawnImperialStarShuttle();
	float ImperialStarShuttleSpawnTimer;

};

#endif // SpaceShipManager_h__