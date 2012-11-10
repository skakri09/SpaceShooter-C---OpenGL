/********************************************************************
    created:    9:11:2012   21:13
    filename:   GameStateManager.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef GameStateManager_h__
#define GameStateManager_h__

#include <gl/glew.h>
#include <SDL.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>
#include <sstream>

#include "GameState.h"
#include "MainMenu.h"
#include "GameManager.h"
#include "GameConstants.h"
#include "InputManager.h"
#include "Timer.h"
#include "Texturable.h"
#include "Logger.h"
#include "TextFactory.h"

class GameStateManager
{
public:
    GameStateManager();
    ~GameStateManager();

	void InitGameStateManager();

	void SwitchState(GameState newState);

	void GameLoop();

private:
	Logger log;
	bool exit;
	GameState currentState;
	GameState switchToState;
	void UpdateCurrentState();
	void DrawCurrentState();

	//Gameplay states:
	void OnSwitchToGameState();
	void SetGameLights();
	void SetGameFog();

	//Menu states:
	void OnSwitchToMenuState();
	void SetMenuLights();
	void SetMenuFog();

	std::shared_ptr<GameManager> game;
	std::shared_ptr<MainMenu> menu;

	bool gameWasInited;
	bool menuWasInited;
private: //One-time inits:
	InputManager input;
	Timer timer;
	float deltaTime;

	void CreateOpenGLContext();
	void InitGlew();
	void InitDevil();
	void DisplayLoadingScreen();
};

#endif // GameStateManager_h__