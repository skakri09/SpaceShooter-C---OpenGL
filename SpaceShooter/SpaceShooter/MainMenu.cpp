#include "MainMenu.h"


MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init(InputManager* input, bool* quitGame)
{
	skybox.initSkybox("skybox1", 100);
	this->input = input;

	playGameEntry = std::make_shared<PlayGameEntry>(0.0f, 2.0f, 0.0f, 0.08f);
	quitGameEntry = std::make_shared<QuitGameEntry>(quitGame, 0.0f, -5.0f, 0.0f, 0.08f);
}

void MainMenu::UpdateMenu(float deltaTime)
{
	skybox.UpdateSkybox(deltaTime);
	playGameEntry->UpdateEntry(deltaTime);
	quitGameEntry->UpdateEntry(deltaTime);
}

void MainMenu::DrawMenu()
{
	skybox.drawSkybox();

	playGameEntry->DrawEntry();
	quitGameEntry->DrawEntry();
}

