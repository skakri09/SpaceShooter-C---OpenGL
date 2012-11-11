#include "OptionsMenu.h"


OptionsMenu::OptionsMenu()
	:Menu("skybox1")
{
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::Init( InputManager* input, GameState* gameState )
{
	menuEntries.push_back(std::make_shared<TogglePolygonSmoothEnabledEntry>(0.0f, 0.0f, 0.0f, 0.04f));
	menuEntries.push_back(std::make_shared<BackToMainMenuEntry>(gameState, 0.0f, -5.0f, 0.0f, 0.08f));
	
	Menu::Init(input, gameState);

	menuEntries.at(selectedEntry)->SetIsSelected(true);
}
