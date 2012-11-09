/********************************************************************
    created:    9:11:2012   15:57
    filename:   PlayGameEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef PlayGameEntry_h__
#define PlayGameEntry_h__

#include "MenuEntry.h"
#include "GameState.h"

class PlayGameEntry : public MenuEntry
{
public:
    PlayGameEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale);
    ~PlayGameEntry();

	virtual void OnClicked();

protected:

private:
	GameState* gameState;
};

#endif // PlayGameEntry_h__