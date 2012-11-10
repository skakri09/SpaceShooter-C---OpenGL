#include "QuitGameEntry.h"


QuitGameEntry::QuitGameEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale)
	: MenuEntry("Quit Game", xPos, yPos, zPos, scale)
{
	this->gameState = gameState;
}

QuitGameEntry::~QuitGameEntry()
{
}

void QuitGameEntry::OnClicked()
{
	*gameState = QUIT;
}
