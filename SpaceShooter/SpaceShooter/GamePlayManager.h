/********************************************************************
    created:    6:10:2012   9:42
    filename:   GamePlayManager.h
    author:     Kristian Skarseth
    
	purpose:    This class acts as the game manager, calling all the
				other classes needed for the game. It uses SDL for 
				rendering and glm for opengl stuff.
*********************************************************************/
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <memory>
#include <SDL.h>

#include "TextFactory.h"
#include "MainMenu.h"
#include "Timer.h"
#include "SpaceShipManager.h"
#include "InputManager.h"
#include "ParticleManager.h"
#include "GameConstants.h"
#include "Camera.h"
#include "Texturable.h"
#include "ProjectileManager.h"
#include "EnvironmentalManager.h"
#include "GameState.h"
#include "GameplayGUI.h"

#include <gl/glew.h>
#include <gl/gl.h>

//Forward declaring InputManager class as this class rely on it,
//and the InputManager class rely on this class.
class InputManager;

class GamePlayManager 
{
public:
	GamePlayManager();  //ctor
	~GamePlayManager(); //dtor

	//Initializes the game, including the OpenGL context
	//and data required
	void InitGamePlayManager(InputManager* input, GameState* gameState);

	//Function that calls all render functions from other managers
	void RenderGame();

	//function that calls all update functions from other managers
	//and takes care of swapping buffers
	void UpdateGame(float deltaTime);

	void OnEnteringGameState();

private:
	Logger log;
	GameState* gameState;
	InputManager* input;
	EnvironmentalManager environment;
	Camera cam;

	GameplayGUI gpi;
	void SetGameLights();
	void SetGameFog();
};

#endif // _GAMEMANAGER_H_
