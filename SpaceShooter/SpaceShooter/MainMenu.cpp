#include "MainMenu.h"


MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init(InputManager* input, bool* quitGame, GameState* gameState)
{
	skybox.initSkybox("skybox1", 100);
	this->input = input;
	selectedEntry = 0;

	playGameEntry = std::make_shared<PlayGameEntry>(gameState, 0.0f, 2.0f, 0.0f, 0.08f);
	quitGameEntry = std::make_shared<QuitGameEntry>(quitGame, 0.0f, -5.0f, 0.0f, 0.08f);
	menuEntries.push_back(playGameEntry);
	menuEntries.push_back(quitGameEntry);
	
	menuEntries.at(selectedEntry)->SetIsSelected(true);
}

void MainMenu::UpdateMenu(float deltaTime)
{
	skybox.UpdateSkybox(deltaTime);
	HandleInput();
	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->UpdateEntry(deltaTime);
	}
}

void MainMenu::DrawMenu()
{
	skybox.drawSkybox();

	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->DrawEntry();
	}
}

void MainMenu::HandleInput()
{
	if(input->KeyDownOnce(SDLK_s))// && !input->KeyDownOnce(SDLK_w))
	{
		if(selectedEntry >= menuEntries.size()-1)
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			selectedEntry = 0;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
		else
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			++selectedEntry;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
	}
	else if(input->KeyDownOnce(SDLK_w) && !input->KeyDownOnce(SDLK_s))
	{
		if(selectedEntry <= 0)
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			selectedEntry = menuEntries.size()-1;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
		else
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			--selectedEntry;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
	}

	if(input->KeyDownOnce(SDLK_RETURN) || input->KeyDownOnce(SDLK_SPACE))
	{
		menuEntries.at(selectedEntry)->OnClicked();
	}
}

