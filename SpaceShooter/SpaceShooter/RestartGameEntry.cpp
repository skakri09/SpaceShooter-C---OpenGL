#include "RestartGameEntry.h"

RestartGameEntry::RestartGameEntry(GameState* gameState, 
	float xPos, float yPos, float zPos, float scale)
	:MenuEntry("Restart Game", xPos, yPos, zPos, scale)
{
	this->gameState = gameState;
}

RestartGameEntry::~RestartGameEntry()
{

}

void RestartGameEntry::OnClicked()
{
	*gameState = NEW_GAME;
}
