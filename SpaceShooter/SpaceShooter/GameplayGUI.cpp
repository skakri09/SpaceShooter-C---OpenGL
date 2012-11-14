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
	GuiEntries.push_back(std::make_shared<ProjectileIcon>(LASER_FAST,"SingleLaser.png", -6.1f, 3.40f, -5.0f, 0.8f));
	GuiEntries.push_back(std::make_shared<ProjectileIcon>(DOUBLE_LASER,"DoubleLaser.png", -5.2f, 3.40f, -5.0f, 0.8f));
	GuiEntries.push_back(std::make_shared<ProjectileIcon>(TRIPLE_CONE_LASER,"TripleLaser.png", -4.3f, 3.40f, -5.0f, 0.8f));
	GuiEntries.push_back(std::make_shared<ProjectileIcon>(QUAD_LASER,"QuadLaser.png", -3.4f, 3.40f, -5.0f, 0.8f));
	GuiEntries.push_back(std::make_shared<ProjectileIcon>(DOUBLE_TRIPLE_CONE_LASER,"DoubleTripleLaser.png", -2.5f, 3.40f, -5.0f, 0.8f));

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
