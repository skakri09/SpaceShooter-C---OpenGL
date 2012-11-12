#include "MainMenu.h"


MainMenu::MainMenu()
	:log("mainMenu", WARN),
	Menu("skybox1")
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init(InputManager* input, GameState* gameState)
{
	menuEntries.push_back(std::make_shared<PlayGameEntry>(gameState, 0.0f, 0.0f, 0.0f, 0.08f));
	menuEntries.push_back(std::make_shared<OptionsEntry>(gameState, 0.0f, -5.0f, 0.0f, 0.08f));
	menuEntries.push_back(std::make_shared<QuitGameEntry>(gameState, 0.0f, -10.0f, 0.0f, 0.08f));

	Menu::Init(input, gameState);

	menuEntries.at(selectedEntry)->SetIsSelected(true);
}

void MainMenu::UpdateMenu(float deltaTime)
{
	Menu::UpdateMenu(deltaTime);
}

void MainMenu::RenderMenu()
{
	Menu::RenderMenu();
}

void MainMenu::OnEnteringMenu(GameState* gameState)
{
	Menu::OnEnteringMenu(gameState);

	SoundManager::Inst()->PlaySong("imperial_march");
}
