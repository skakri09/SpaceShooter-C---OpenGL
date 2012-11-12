/********************************************************************
    created:    11:11:2012   12:53
    filename:   OptionsMenu.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef OptionsMenu_h__
#define OptionsMenu_h__

#include "Menu.h"
#include "BackEntry.h"
#include "TogglePolygonSmoothEnabledEntry.h"
#include "ToggleSoundMute.h"
#include "ToggleMusicMute.h"
#include "ToggleEffectsMute.h"

class OptionsMenu : public Menu
{
public:
    OptionsMenu();
    ~OptionsMenu();

	void Init(InputManager* input, GameState* gameState);

	void SetBackState(GameState state);

protected:

private:
	std::shared_ptr<BackEntry> backEntry;
};

#endif // OptionsMenu_h__