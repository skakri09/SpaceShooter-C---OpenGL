#include "IngameMenu.h"

IngameMenu::IngameMenu()
	: Menu("skybox3")
{
}

IngameMenu::~IngameMenu()
{
}

void IngameMenu::Init(InputManager* input, GameState* gameState)
{
	menuEntries.push_back(std::make_shared<ResumeGameEntry>(gameState, 0.0f, 5.0f, 0.0f, 0.08f));
	menuEntries.push_back(std::make_shared<RestartGameEntry>(gameState, 0.0f, 0.0f, 0.0f, 0.08f));
	menuEntries.push_back(std::make_shared<OptionsEntry>(gameState, 0.0f, -5.0f, 0.0f, 0.08f));
	menuEntries.push_back(std::make_shared<BackToMainMenuEntry>(gameState, 0.0f, -10.0f, 0.0f, 0.08f));

	Menu::Init(input, gameState);

	menuEntries.at(selectedEntry)->SetIsSelected(true);
}

void IngameMenu::UpdateMenu(float deltaTime)
{
	Menu::UpdateMenu(deltaTime);
}

void IngameMenu::RenderMenu()
{
	Menu::RenderMenu();
}

void IngameMenu::OnEnteringMenu(GameState* gameState)
{
	Menu::OnEnteringMenu(gameState);
	SoundManager::Inst()->PlaySong("throne_room");
}
