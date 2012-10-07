#include "GameManager.h"
#include "GLUtils/GLUtils.hpp"


#include <Windows.h>
#include <GL/GL.h>
//#include <gl/glew.h>

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
	: log("GameMan", WARN)
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

void GameManager::setOpenGLStates() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glShadeModel(GL_SMOOTH); 
	//glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
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

	//initializing glew, if not called before we start initializing
	//the the game objects we will crash when trying to access
	//glew functions
	if(glewInit() != GLEW_OK)
	{
		log << ERRORX << "GlewInit() failed" << std::endl;
	}

	//A resize MUST be called before we start, as it does 
	//the gluPerspective() and glViewPort() calls 
	//+ some other stuff
	input.resize(window_width, window_height);

	shipManager.InitManager(&input);
	particleManager.InitParticleManager();
}

void GameManager::render() {
	//Clear screen, and set the correct program
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	particleManager.DrawParticles();
	shipManager.DrawSpaceShips();

	checkGLErrors();
	SDL_GL_SwapBuffers();
}

void GameManager::update()
{
	input.Update(doExit);

	particleManager.UpdateParticles(deltaTime);
	shipManager.UpdateManager(deltaTime);
}

void GameManager::GameLoop() 
{
	doExit = false;

	//The gameloop. Handling the delta time and calling
	//the update and render functions which takes care of
	//the various managers
	int fps = 0;
	GLfloat sec = 0;
	while (!doExit) 
	{
		//storing delta time in a class variable. Casting to GLfloat since
		//we basically use that in the whole project
		deltaTime = static_cast<GLfloat>(my_timer.elapsedAndRestart());
		sec += deltaTime;
		fps++;
		if(sec >= 1.0f)
		{
			log << WARN << fps << std::endl;
			fps = 0;
			sec = 0;
		}
		update();
		render();		
	}

	quit();
}

void GameManager::quit() {
	std::cout << "Bye bye..." << std::endl;
}


