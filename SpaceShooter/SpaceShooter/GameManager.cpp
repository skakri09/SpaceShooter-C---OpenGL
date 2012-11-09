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
	: log("GameMan", WARN)
{
	my_timer.restart();
	srand(static_cast<unsigned int>(time(0)));
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

	SDL_WM_SetCaption("NITH - PG430 Space Invaders - FPS: 0", "");

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	if (SDL_SetVideoMode(window_width, window_height, 0, SDL_OPENGL
		| SDL_DOUBLEBUF | SDL_RESIZABLE) == NULL) {
			std::stringstream err;
			err << "SDL_SetVideoMode failed ";
			throw std::runtime_error(err.str());
	}
}

void GameManager::setOpenGLStates() 
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

void GameManager::init() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::stringstream err;
		err << "Could not initialize SDL: " << SDL_GetError();
		throw std::runtime_error(err.str());
	}
	atexit( SDL_Quit);
	
	createOpenGLContext();
	

	//initializing glew, if not called before we start initializing
	//the the game objects we will crash when trying to access
	//glew functions
	if(glewInit() != GLEW_OK)
	{
		log << ERRORX << "GlewInit() failed" << std::endl;
	}

	// Initialize DevIL
	ilInit();
	iluInit();
	//Setting origin to upper left. I had problems getting it to work with lowerleft
	//so just went with upper left. It takes some getting used to when working with 
	//texcoords, but it works.
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilEnable(IL_ORIGIN_SET);

	DisplayLoadingScreen();
	setOpenGLStates();
	TextFactory::Inst()->InitTextFactory();
	ProjectileManager::Inst()->InitProjectileManager();
	SpaceShipManager::Inst()->InitManager(&input);
	ParticleManager::Inst()->InitParticleManager();
	environment.InitManager();
	skybox.initSkybox("skybox1", 100);
	
	//A resize MUST be called before we start, as it does 
	//the gluPerspective() and glViewPort() calls 
	//+ some other stuff
	input.resize(window_width, window_height);
	rotate = 0;
	currentGameState = GAME;
	menu.Init(&input);
}

void GameManager::RenderGame() 
{
	//Clear screen, and set the correct program
	glPushMatrix();

	glPushMatrix();
	glLoadIdentity();
	//rotating the spacebox slightly to make it look more alive.
	glRotatef(rotate, 0, 1, 0);

	skybox.drawSkybox();
	glPopMatrix();

	glClear(GL_DEPTH_BUFFER_BIT);
	environment.DrawEnvironment();
	ParticleManager::Inst()->DrawParticles();
	SpaceShipManager::Inst()->DrawSpaceShips();
	ProjectileManager::Inst()->DrawProjectiles();
	checkGLErrors();
	glPopMatrix();
}

void GameManager::UpdateGame()
{
	rotate += deltaTime*1.5f;
	if(rotate >= 360)
	{
		rotate -=360;
	}

	environment.Update(deltaTime);
	ParticleManager::Inst()->UpdateParticles(deltaTime);
	SpaceShipManager::Inst()->UpdateManager(deltaTime, doExit);
	ProjectileManager::Inst()->UpdateProjectiles(deltaTime);
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
		if(sec >= 1.0f)//updating the fps counter once every second
		{
			log << INFO << fps << std::endl;
			std::ostringstream captionStream;
			captionStream << "NITH - PG430 Space Invaders - FPS: ";
			captionStream << fps;
			captionStream << "  -  Player HP: ";
			captionStream << SpaceShipManager::Inst()->GetPlayer()->GetSpaceshipHP();
			captionStream << "  - Lives left: ";
			captionStream << SpaceShipManager::Inst()->GetPlayer()->GetLives();
			SDL_WM_SetCaption(captionStream.str().c_str(), "");
			fps = 0;
			sec = 0;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		input.Update(doExit);

		if(currentGameState == GAME)
		{
			UpdateGame();
			RenderGame();
		}
		else if(currentGameState == MENU)
		{
			menu.UpdateMenu(deltaTime);
			menu.DrawMenu();
		}
		SDL_GL_SwapBuffers();
	}

	quit();
}

void GameManager::quit() {
	std::cout << "Bye bye..." << std::endl;
}

void GameManager::DisplayLoadingScreen()
{
	Texturable texturable;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	texturable.InitTexture("..//images//LoadingScreen.jpg", "loadingscreen");
	texturable.BindTexture("loadingscreen");
	
	glScalef(2, 2, 2);
	
	
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.5f, 0.0f);//bottomleft
	
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.5f, 0.0f);//bottomright
	
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.5f, 0.0f);//topright

	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.5f, 0.0f);//topleft
	glEnd();
	
	texturable.UnbindTexture();
	SDL_GL_SwapBuffers();
}

void GameManager::SetLights()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	const static GLfloat ambient[] = 
	{ 0.0f, 0.0f, 0.0f, 1.0f };
	const static GLfloat diffuse[] = 
	{ 1.0f, 1.0f, 1.0f, 0.5f };
	const static GLfloat specular[] = 
	{ 0.0f, 1.0f, 0.0f, 1.0f };
	const static GLfloat position[] = 
	{ 0.0f, 0.0f, -500.0, 1.0f }; 
	const static GLfloat position2[] = 
	{ -500.0f, -500.0f, 0.0, 0.0f }; 

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);      
}

void GameManager::SetFog()
{
	GLfloat fogColor[4]= {0.0f, 0.0f, 0.0f, 1.0f}; 
	//GL_EXP, GL_EXP2, GL_LINEAR
	glFogi(GL_FOG_MODE, GL_LINEAR);       
	glFogfv(GL_FOG_COLOR, fogColor);           
	glFogf(GL_FOG_DENSITY, 0.45f);          
	glHint(GL_FOG_HINT, GL_NICEST);      
	glFogf(GL_FOG_START, 300.0f);         
	glFogf(GL_FOG_END, FRUSTUM_DEPTH);              
	glEnable(GL_FOG);   
}


