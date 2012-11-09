#include "MainMenu.h"


MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init(InputManager* input)
{
	skybox.initSkybox("skybox1", 100);
}

void MainMenu::UpdateMenu(float deltaTime)
{
	skybox.UpdateSkybox(deltaTime);
	playGame.UpdateEntry(deltaTime);
}

void MainMenu::DrawMenu()
{
	skybox.drawSkybox();

	playGame.DrawEntry();
}

