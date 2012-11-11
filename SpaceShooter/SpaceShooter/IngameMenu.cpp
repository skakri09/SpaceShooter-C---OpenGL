#include "IngameMenu.h"

IngameMenu::IngameMenu()
	: Menu("skybox1")
{
}

IngameMenu::~IngameMenu()
{
}

void IngameMenu::Init(InputManager* input, GameState* gameState)
{

	menuEntries.push_back(std::make_shared<BackToMainMenuEntry>(gameState, 0.0f, 0.0f, 0.0f, 0.08f));

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

void IngameMenu::OnEnteringMenu()
{
	Menu::OnEnteringMenu();
	SoundManager::Inst()->PlaySong("imperial_march");
}
