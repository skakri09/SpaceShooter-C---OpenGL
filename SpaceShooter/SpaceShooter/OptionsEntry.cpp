#include "OptionsEntry.h"


OptionsEntry::OptionsEntry(GameState* gameState, float xPos, float yPos, float zPos, float scale)
	:MenuEntry("Options", xPos, yPos, zPos, scale)
{
	this->gameState = gameState;
}

OptionsEntry::~OptionsEntry()
{
}

void OptionsEntry::OnClicked()
{
	*gameState = OPTIONS;
}