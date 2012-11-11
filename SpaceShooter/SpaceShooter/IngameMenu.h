/********************************************************************
    created:    11:11:2012   18:01
    filename:   IngameMenu.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef IngameMenu_h__
#define IngameMenu_h__

#include "Menu.h"
#include "MenuEntry.h"
#include "BackToMainMenuEntry.h"
#include "RestartGameEntry.h"
#include "ResumeGameEntry.h"

class IngameMenu : public Menu
{
public:
    IngameMenu();
    ~IngameMenu();

	void Init(InputManager* input, GameState* gameState);

	void UpdateMenu(float deltaTime);

	void RenderMenu();

	void OnEnteringMenu();

protected:

private:

};

#endif // IngameMenu_h__