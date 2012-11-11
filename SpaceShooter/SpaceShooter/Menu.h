/********************************************************************
    created:    11:11:2012   12:55
    filename:   Menu.h
    author:     Kristian Skarseth
    
    purpose:    Base for any menu
*********************************************************************/
#ifndef Menu_h__
#define Menu_h__

#include "MenuEntry.h"
#include "GameState.h"
#include "PlayerSpaceShip.h"
#include "InputManager.h"
#include "Camera.h"

class Menu
{
public:
    Menu(std::string skyboxName);
    ~Menu();

	//Sets default camera position, loads the skybox that was defined in
	//the constructor and stores a local pointer of the input manager and game state
	virtual void Init(InputManager* input, GameState* gameState);

	//Handles input and loops trough all menu entries, calling their update
	virtual void UpdateMenu(float deltaTime);

	//Renders the camera(skybox) and all the menu entries
	virtual void RenderMenu();

	//Resets the menu to it's default state, positioning lights, enabling/disabling
	//openGL states etc
	virtual void OnEnteringMenu();

protected:
	virtual void UpdateSelectionShip(float deltaTime);

	virtual void HandleInput();

	std::vector<std::shared_ptr<MenuEntry>> menuEntries;

	std::shared_ptr<PlayerSpaceShip> menuShip;

	InputManager* input;
	GameState* gameState;

	Camera cam;

	unsigned int selectedEntry;

	float deltaTime;

private:
	std::string skyboxName;
};

#endif // Menu_h__