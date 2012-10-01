#include "GameManager.h"
#include "GLUtils/GLUtils.hpp"


#include <Windows.h>
#include <GL/GL.h>


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <stdexcept>

using std::cerr;
using std::endl;
using GLUtils::checkGLErrors;

GameManager::GameManager()
	: log("GameMan", WARN),
	player(0.f, 0.f, 0.0f, 0.0f)
{
	my_timer.restart();
}

GameManager::~GameManager() {

}

void GameManager::createOpenGLContext() {
	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Use double buffering
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); // Use framebuffer with 16 bit depth buffer
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Use framebuffer with 8 bit for red
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // Use framebuffer with 8 bit for green
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // Use framebuffer with 8 bit for blue
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Use framebuffer with 8 bit for alpha

	SDL_WM_SetCaption("NITH - PG430 Space Invaders", "");

	// Initalize video
	if (SDL_SetVideoMode(window_width, window_height, 0, SDL_OPENGL
		| SDL_DOUBLEBUF | SDL_RESIZABLE) == NULL) {
			std::stringstream err;
			err << "SDL_SetVideoMode failed ";
			throw std::runtime_error(err.str());
	}
}

void GameManager::resize(unsigned int width, unsigned int height) {
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.5f, 1.0f, 500.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GameManager::setOpenGLStates() {
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	//glShadeModel(GL_SMOOTH); 
	glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
}

void GameManager::init() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::stringstream err;
		err << "Could not initialize SDL: " << SDL_GetError();
		throw std::runtime_error(err.str());
	}
	atexit( SDL_Quit);

	createOpenGLContext();
	setOpenGLStates();

	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.5f, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//resize(window_width, window_height);

	player.CreateDrawable();
}

void GameManager::render() {
	//Clear screen, and set the correct program
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player.Draw(deltaTime);
	//proj.Draw(deltaTime);
	
//	checkGLErrors();
}

void GameManager::play() 
{
	bool doExit = false;

	//SDL main loop
	while (!doExit) 
	{
		deltaTime = (GLfloat) my_timer.elapsedAndRestart();
		
		input.Update(doExit);
	
		if(input.Fire())
		{
			player.FireGun(deltaTime);
		}

		HandleXAxisMovement();
		HandleYAxisMovement();
		HandleFrustumCollision();

		//log << INFO << "X: " << xPos << " Y: " << yPos << std::endl;
		//Render, and swap front and back buffers
		render();
		SDL_GL_SwapBuffers();
	}
	quit();
}

void GameManager::quit() {
	std::cout << "Bye bye..." << std::endl;
}

void GameManager::HandleXAxisMovement()
{
	if (input.MoveLeft()|| input.MoveRight())
	{
		//if left and right
		if (input.MoveLeft() && input.MoveRight())
		{
			player.setXVel(0.0f);
		}
		//If only left
		if (input.MoveLeft() && !input.MoveRight())
		{
			player.setXVel(-PLAYER_X_VELOCITY);
		}
		//If only right
		if (!input.MoveLeft() && input.MoveRight())
		{
			player.setXVel(PLAYER_X_VELOCITY);
		}
	}
	else
	{
		//No movement
		player.setXVel(0.0f);
	}
}

void GameManager::HandleYAxisMovement()
{
	if (input.MoveUp()|| input.MoveDown())
	{
		//if up and down
		if (input.MoveUp() && input.MoveDown())
		{
			player.setYVel(0.0f);
		}
		//If only up
		if (input.MoveUp() && !input.MoveDown())
		{
			player.setYVel(PLAYER_Y_VELOCITY);
		}
		//If only down
		if (!input.MoveUp() && input.MoveDown())
		{
			player.setYVel(-PLAYER_Y_VELOCITY);
		}
	}
	else
	{
		//No movement
		player.setYVel(0.0f);
	}
}

void GameManager::HandleFrustumCollision()
{
	if( (player.getXPos() >= FRUSTUM_RIGHT && player.getXVel() > 0.0f) || 
		(player.getXPos() <= FRUSTUM_LEFT && player.getXVel() < 0.0f))
	{
		player.setXVel(0.0f);
	}
	if( (player.getYPos() >= FRUSTUM_TOP && player.getYVel() > 0.0f) || 
		(player.getYPos() <= FRUSTUM_BOTTOM && player.getYVel() < 0.0f))
	{
		player.setYVel(0.0f);
	}
		log << INFO << player.getYPos() << std::endl;
}

