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
#include "GamePlayManager.h"
#include "GameConstants.h"
#include "InputManager.h"
#include "Timer.h"
#include "Texturable.h"
#include "Logger.h"
#include "TextFactory.h"
#include "OptionsMenu.h"
#include "SoundManager.h"
#include "VBODrawable.h"
#include "IngameMenu.h"

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

	std::shared_ptr<GamePlayManager> game;
	std::shared_ptr<MainMenu> mainMenu;
	std::shared_ptr<OptionsMenu> options;
	std::shared_ptr<IngameMenu> ingameMenu;

	bool gameWasInited;
	bool menuWasInited;
	bool optionsWasInited;
	bool ingameMenuWasInited;

private: //One-time inits:
	InputManager input;
	Timer timer;
	float deltaTime;
	//SMPEGPlayer smpeg;
	void CreateOpenGLContext();
	void InitGlew();
	void InitDevil();
	void DisplayLoadingScreen();
	
	void HandleInput();

	SDL_Surface* screen;

	void SetOpenGLVideoMode();
	void SetSDLVideoMode();
};

#endif // GameStateManager_h__