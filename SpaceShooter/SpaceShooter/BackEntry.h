/********************************************************************
    created:    11:11:2012   20:08
    filename:   BackEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef BackEntry_h__
#define BackEntry_h__

#include "MenuEntry.h"
#include "GameState.h"

class BackEntry : public MenuEntry
{
public:
    BackEntry(GameState* gameState,
		float xPos, float yPos, float zPos, float scale);
    ~BackEntry();

	void OnClicked();

	void SetBackToState(GameState backState);

protected:

private:
	GameState* gameState;
	GameState backToState;
};

#endif // BackEntry_h__