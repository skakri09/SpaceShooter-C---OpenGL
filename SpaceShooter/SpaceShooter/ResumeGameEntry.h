/********************************************************************
    created:    11:11:2012   19:21
    filename:   ResumeGameEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ResumeGameEntry_h__
#define ResumeGameEntry_h__

#include "MenuEntry.h"
#include "GameState.h"
class ResumeGameEntry : public MenuEntry
{
public:
    ResumeGameEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale);
    ~ResumeGameEntry();

	void OnClicked();
protected:

private:
	GameState* gameState;
};

#endif // ResumeGameEntry_h__