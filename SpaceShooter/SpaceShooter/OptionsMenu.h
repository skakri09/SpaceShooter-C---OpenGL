/********************************************************************
    created:    11:11:2012   12:53
    filename:   OptionsMenu.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef OptionsMenu_h__
#define OptionsMenu_h__

#include "Menu.h"
#include "BackToMainMenuEntry.h"
#include "TogglePolygonSmoothEnabledEntry.h"

class OptionsMenu : public Menu
{
public:
    OptionsMenu();
    ~OptionsMenu();

	void Init(InputManager* input, GameState* gameState);

protected:

private:

};

#endif // OptionsMenu_h__