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
	PlayGameEntry playGame;
}

void MainMenu::UpdateMenu(float deltaTime)
{
	
}

void MainMenu::DrawMenu()
{
	skybox.drawSkybox();
}

