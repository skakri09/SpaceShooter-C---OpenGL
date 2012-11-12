#include "OptionsMenu.h"


OptionsMenu::OptionsMenu()
	:Menu("skybox3")
{
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::Init( InputManager* input, GameState* gameState )
{
	menuEntries.push_back(std::make_shared<ToggleSoundMute>(0.0f, 5.0f, 0.0f, 0.04f));
	menuEntries.push_back(std::make_shared<ToggleMusicMute>(0.0f, 2.0f, 0.0f, 0.04f));
	menuEntries.push_back(std::make_shared<ToggleEffectsMute>(0.0f, -1.0f, 0.0f, 0.04f));
	menuEntries.push_back(std::make_shared<TogglePolygonSmoothEnabledEntry>(0.0f, -4.0f, 0.0f, 0.04f));
	
	backEntry = std::make_shared<BackEntry>(gameState, 0.0f, -15.0f, 0.0f, 0.08f);
	menuEntries.push_back(backEntry);
	
	Menu::Init(input, gameState);

	menuEntries.at(selectedEntry)->SetIsSelected(true);
}

void OptionsMenu::SetBackState( GameState state )
{
	backEntry->SetBackToState(state);
}
