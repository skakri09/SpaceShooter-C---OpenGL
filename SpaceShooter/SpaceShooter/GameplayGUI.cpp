#include "GameplayGUI.h"


GameplayGUI::GameplayGUI()
{
}

GameplayGUI::~GameplayGUI()
{
}

void GameplayGUI::InitGUI(ManagerInterface* manager)
{

	GuiEntries.push_back(std::make_shared<HPEntry>());
	GuiEntries.push_back(std::make_shared<LivesEntry>());
	GuiEntries.push_back(std::make_shared<ScoreTextEntry>());
	for(unsigned int i = 0; i < GuiEntries.size(); i++)
	{
		GuiEntries.at(i)->Init();
	}

	GuiEntries.push_back(std::make_shared<ScoreValueEntry>());
	GuiEntries.back()->Init(manager);
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
	
}
