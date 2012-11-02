/********************************************************************
    created:    6:10:2012   9:42
    filename:   GameManager.h
    author:     Kristian Skarseth
    
	purpose:    This class acts as the game manager, calling all the
				other classes needed for the game. It uses SDL for 
				rendering and glm for opengl stuff.
*********************************************************************/
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <memory>
#include <SDL.h>

#include "Timer.h"
#include "GameObject.h"
#include "SpaceShipManager.h"
#include "InputManager.h"
#include "ParticleManager.h"
#include "GameConstants.h"
#include "Skybox.h"

#include <gl/glew.h>
#include <gl/gl.h>

//Forward declaring InputManager class as this class rely on it,
//and the InputManager class rely on this class.
class InputManager;

class GameManager 
{
public:
	GameManager();  //ctor
	~GameManager(); //dtor

	//Initializes the game, including the OpenGL context
	//and data required
	void init();

	// The main loop of the game. Runs the SDL main loop
	void GameLoop();

	// Quit function 
	void quit();

	//Function that calls all render functions from other managers
	void render();

	//function that calls all update functions from other managers
	//and takes care of swapping buffers
	void update();
	
	//Function that is called when the window is resized
	void resize(unsigned int width, unsigned int height);

private:

	//Creates the OpenGL context using SDL
	void createOpenGLContext();

	//Sets states for OpenGL that we want to keep persistent
	//throughout the game
	void setOpenGLStates();

	float rotate;
private:
	Logger log;

	Timer my_timer;		//Timer for machine independent motion
	GLfloat deltaTime;	//Time since last update 


	//Manager handling all the particle effects in the game
	//ParticleManager particleManager;

	//Manager handling all the spaceships, both player and enemies
	SpaceShipManager shipManager;

	//Inputmanager, requires an update call each gameloop to be updated
	//and ready for input queries
	InputManager input;

	//Our skybox
	Skybox skybox;

	bool doExit; //If true, the game quits
};

#endif // _GAMEMANAGER_H_
