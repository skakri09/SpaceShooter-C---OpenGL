#include "BackToMainMenuEntry.h"


BackToMainMenuEntry::BackToMainMenuEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale)
	: MenuEntry("back to menu", xPos, yPos, zPos, scale)
{
	this->gameState = gameState;
}

BackToMainMenuEntry::~BackToMainMenuEntry()
{
}

void BackToMainMenuEntry::OnClicked()
{
	*gameState = MAIN_MENU;
}
