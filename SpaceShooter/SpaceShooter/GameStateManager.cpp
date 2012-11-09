#include "GameStateManager.h"


GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::SwitchState( GameState newState )
{
	switch(newState)
	{
	case GAME:
		OnSwitchToGameState();
		break;
	case MENU:
		OnSwitchToMenuState();
		break;
	}
}

void GameStateManager::OnSwitchToGameState()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glShadeModel(GL_SMOOTH); 

	SetLights();
	SetFog();
}

void GameStateManager::OnSwitchToMenuState()
{

}
