#include "PlayGameEntry.h"


PlayGameEntry::PlayGameEntry(float xPos, float yPos, float zPos, float scale)
	:MenuEntry("Play Game", xPos, yPos, zPos, scale)
{
}

PlayGameEntry::~PlayGameEntry()
{
}

void PlayGameEntry::OnClicked()
{
	//start game
}
