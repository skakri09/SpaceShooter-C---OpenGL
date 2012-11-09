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

#include "Skybox.h"
#include "InputManager.h"
#include "MenuEntry.h"
#include "PlayGameEntry.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

	void Init(InputManager* input);

	void UpdateMenu(float deltaTime);

	void DrawMenu();
protected:

private:
	Skybox skybox;

	PlayGameEntry playGame;

};

#endif // MainMenu_h__