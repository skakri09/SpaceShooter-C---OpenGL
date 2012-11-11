/********************************************************************
    created:    11:11:2012   13:18
    filename:   BackToMainMenuEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef BackToMainMenuEntry_h__
#define BackToMainMenuEntry_h__

#include "MenuEntry.h"
#include "GameState.h"

class BackToMainMenuEntry : public MenuEntry
{
public:
    BackToMainMenuEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale);
    ~BackToMainMenuEntry();

	virtual void OnClicked();

private:
	GameState* gameState;
};

#endif // BackToMainMenuEntry_h__