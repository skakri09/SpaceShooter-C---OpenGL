#include "BackEntry.h"

BackEntry::BackEntry( GameState* gameState,
	float xPos, float yPos, float zPos, float scale )
	:MenuEntry("Back", xPos, yPos, zPos, scale)
{
	this->gameState = gameState;
	this->backToState = MAIN_MENU; //default backtostate
}

BackEntry::~BackEntry()
{

}

void BackEntry::OnClicked()
{
	*gameState = backToState;
}

void BackEntry::SetBackToState(GameState backState)
{
	this->backToState = backState;
}
