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

#include "InputManager.h"
#include "MenuEntry.h"
#include "PlayGameEntry.h"
#include "QuitGameEntry.h"
#include "GameState.h"
#include "PlayerSpaceShip.h"
#include "Vector3d.h"
#include "Camera.h"
#include "Logger.h"
#include "OptionsEntry.h"
#include "Menu.h"
#include "SoundManager.h"

class MainMenu : public Menu
{
public:
    MainMenu();
    ~MainMenu();

	void Init(InputManager* input, GameState* gameState);

	void UpdateMenu(float deltaTime);

	void RenderMenu();
	
	void OnEnteringMenu();

private:
	Logger log;

};

#endif // MainMenu_h__