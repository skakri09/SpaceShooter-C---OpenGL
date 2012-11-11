/********************************************************************
    created:    11:11:2012   12:45
    filename:   OptionsEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef OptionsEntry_h__
#define OptionsEntry_h__

#include "MenuEntry.h"
#include "GameState.h"

class OptionsEntry : public MenuEntry
{
public:
	OptionsEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale);
	~OptionsEntry();

	void OnClicked();


private:
	GameState* gameState;
};

#endif // OptionsEntry_h__