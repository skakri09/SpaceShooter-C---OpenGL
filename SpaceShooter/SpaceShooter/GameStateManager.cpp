#include "GameStateManager.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;

GameStateManager::GameStateManager()
	:log("GameStateManager", WARN)
{
	timer.restart();
	srand(static_cast<unsigned int>(time(0)));
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::InitGameStateManager()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::stringstream err;
		err << "Could not initialize SDL: " << SDL_GetError();
		throw std::runtime_error(err.str());
	}
	atexit( SDL_Quit);
	CreateOpenGLContext();
	InitGlew();
	InitDevil();
	glEnable(GL_DEPTH_TEST);
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	input.InitInputManager();
	TextFactory::Inst()->InitTextFactory();

	exit = false;
	gameWasInited = false;
	menuWasInited = false;
	game = std::make_shared<GamePlayManager>();
	menu = std::make_shared<MainMenu>();

	SwitchState(GAME);
	switchToState = currentState;
}

void GameStateManager::SwitchState( GameState newState )
{
	switch(newState)
	{
	case GAME:
		log << WARN << "Switching to Game state" << std::endl;

		if(!gameWasInited)
		{
			input.resize(window_width, window_height, true);
			DisplayLoadingScreen();
			input.resize(window_width, window_height);

			game->InitGamePlayManager(&input, &switchToState);
			
			gameWasInited = true;
		}
		currentState = GAME;
		game->OnEnteringGameState();
		break;
	case MENU:
		log << WARN << "Switching to Menu state" << std::endl;

		if(!menuWasInited)
		{
			input.resize(window_width, window_height, true);
			DisplayLoadingScreen();
			input.resize(window_width, window_height);

			menu->Init(&input, &switchToState);
			menuWasInited = true;
		}
		currentState = MENU;
		menu->OnEnteringMenu();
		break;
	case QUIT:
		exit = true;
		break;
	}
}

void GameStateManager::GameLoop()
{
	float fps = 0.0f;
	float sec = 0.0f;
	while(!exit)
	{
		if(switchToState != currentState)
		{
			SwitchState(switchToState);
		}
		deltaTime = static_cast<float>(timer.elapsedAndRestart());
		sec += deltaTime;
		fps++;
		if(sec >= 1.0f)//updating the fps counter once every second
		{
			std::ostringstream captionStream;
			captionStream << "FPS: " << fps;
			SDL_WM_SetCaption(captionStream.str().c_str(), "");
			fps = 0;
			sec = 0;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		input.Update(&switchToState);

		UpdateCurrentState();
		DrawCurrentState();
		
		checkGLErrors();

		SDL_GL_SwapBuffers();
	}
}

void GameStateManager::UpdateCurrentState()
{
	switch(currentState)
	{
	case GAME:
		game->UpdateGame(deltaTime);
		break;
	case MENU:
		menu->UpdateMenu(deltaTime);
		break;
	}
}

void GameStateManager::DrawCurrentState()
{
	switch(currentState)
	{
	case GAME:
		game->RenderGame();
		break;
	case MENU:
		menu->DrawMenu();
		break;
	}
}


// C O N S T A N T   S T A T E S //
//*******************************//
void GameStateManager::CreateOpenGLContext()
{
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
		| SDL_DOUBLEBUF | SDL_RESIZABLE) == NULL) 
	{
		std::stringstream err;
		err << "SDL_SetVideoMode failed ";
		throw std::runtime_error(err.str());
	}
}

void GameStateManager::InitGlew()
{
	//initializing glew, if not called before we start initializing
	//the the game objects we will crash when trying to access
	//glew functions
	if(glewInit() != GLEW_OK)
	{
		log << ERRORX << "GlewInit() failed" << std::endl;
	}
}

void GameStateManager::InitDevil()
{
	// Initialize DevIL
	ilInit();
	iluInit();

	//Setting origin to upper left. I had problems getting it to work with lowerleft
	//so just went with upper left. It takes some getting used to when working with 
	//texcoords, but it works.
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilEnable(IL_ORIGIN_SET);
}


//	   	 O T H E R		 //
//***********************//

void GameStateManager::DisplayLoadingScreen()
{
	glPushMatrix();


	glLoadIdentity();
	Texturable texturable;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
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
	GLuint foo;
	glGenTextures(1,&foo);  //we generate a unique one


	glPopMatrix();
}
