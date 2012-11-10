#include "GameplayGUI.h"


GameplayGUI::GameplayGUI()
{
}

GameplayGUI::~GameplayGUI()
{
}

void GameplayGUI::InitGUI()
{

	GuiEntries.push_back(std::make_shared<HPEntry>());
	GuiEntries.push_back(std::make_shared<LivesEntry>());

	for(unsigned int i = 0; i < GuiEntries.size(); i++)
	{
		GuiEntries.at(i)->Init();
	}
}

void GameplayGUI::UpdateGUI(float deltaTime)
{
	for(unsigned int i = 0; i < GuiEntries.size(); i++)
	{
		GuiEntries.at(i)->Update(deltaTime);
	}
}

void GameplayGUI::RenderGUI()
{
	glPushMatrix();

	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	for(unsigned int i = 0; i < GuiEntries.size(); i++)
	{
		GuiEntries.at(i)->Draw(&vbo);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glClear(GL_DEPTH_BUFFER_BIT);
}
