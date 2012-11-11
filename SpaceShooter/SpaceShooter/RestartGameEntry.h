/********************************************************************
    created:    11:11:2012   18:54
    filename:   RestartGameEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef RestartGameEntry_h__
#define RestartGameEntry_h__

#include "MenuEntry.h"
#include "GameState.h"

class RestartGameEntry : public MenuEntry
{
public:
    RestartGameEntry(GameState* gameState,
					float xPos, float yPos, float zPos, float scale);
    ~RestartGameEntry();

	void OnClicked();

private:
	GameState* gameState;
};

#endif // RestartGameEntry_h__	