#include "PlayGameEntry.h"


PlayGameEntry::PlayGameEntry(GameState* gameState,
	float xPos, float yPos, float zPos, float scale)
	:MenuEntry("Play Game", xPos, yPos, zPos, scale)
{
	this->gameState = gameState;
}

PlayGameEntry::~PlayGameEntry()
{
}

void PlayGameEntry::OnClicked()
{
	*gameState = NEW_GAME;
}
