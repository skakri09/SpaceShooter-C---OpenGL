/********************************************************************
    created:    9:11:2012   19:58
    filename:   QuitGameEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef QuitGameEntry_h__
#define QuitGameEntry_h__

#include "MenuEntry.h"
#include "GameState.h"

class QuitGameEntry : public MenuEntry
{
public:
    QuitGameEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale);
    ~QuitGameEntry();

	virtual void OnClicked();

protected:

private:
	GameState* gameState;
};

#endif // QuitGameEntry_h__