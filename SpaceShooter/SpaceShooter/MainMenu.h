/********************************************************************
    created:    9:11:2012   13:25
    filename:   MainMenu.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef MainMenu_h__
#define MainMenu_h__

#include <SDL.h>
#include <gl/glew.h>
#include <memory>

#include "Skybox.h"
#include "InputManager.h"
#include "MenuEntry.h"
#include "PlayGameEntry.h"
#include "QuitGameEntry.h"
#include "GameState.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

	void Init(InputManager* input, GameState* gameState);

	void UpdateMenu(float deltaTime);

	void DrawMenu();
	
	void OnEnteringMenu();

private:
	Skybox skybox;

	void HandleInput();

	InputManager* input;

	std::shared_ptr<PlayGameEntry> playGameEntry;
	std::shared_ptr<QuitGameEntry> quitGameEntry;

	std::vector<std::shared_ptr<MenuEntry>> menuEntries;

	unsigned int selectedEntry;

	void SetMenuLights();
	void SetMenuFog();
};

#endif // MainMenu_h__