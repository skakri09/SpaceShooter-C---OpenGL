#include "QuitGameEntry.h"


QuitGameEntry::QuitGameEntry(bool* quitGame, float xPos, float yPos, float zPos, float scale)
	: MenuEntry("Quit Game", xPos, yPos, zPos, scale)
{
	this->quitGame = quitGame;
}

QuitGameEntry::~QuitGameEntry()
{
}

void QuitGameEntry::OnClicked()
{
	*quitGame = true;
}
