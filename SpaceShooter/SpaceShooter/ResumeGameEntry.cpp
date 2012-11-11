#include "ResumeGameEntry.h"


ResumeGameEntry::ResumeGameEntry(GameState* gameState, float xPos, 
	float yPos, float zPos, float scale)
	:MenuEntry("resume game", xPos, yPos, zPos, scale)
{
	this->gameState = gameState;
}

ResumeGameEntry::~ResumeGameEntry()
{
}

void ResumeGameEntry::OnClicked()
{
	*gameState = GAME;
}
