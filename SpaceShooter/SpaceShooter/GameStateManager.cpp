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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_MULTISAMPLE);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
	glShadeModel(GL_SMOOTH); 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	DisplayLoadingScreen();

	input.InitInputManager();
	TextFactory::Inst()->InitTextFactory();
	SoundManager::Inst()->InitSoundManager();

	exit = false;
	gameWasInited = false;
	menuWasInited = false;
	optionsWasInited = false;
	ingameMenuWasInited = false;

	game = std::make_shared<GamePlayManager>();
	mainMenu = std::make_shared<MainMenu>();
	options = std::make_shared<OptionsMenu>();
	ingameMenu = std::make_shared<IngameMenu>();

	SwitchState(MAIN_MENU);
	
	switchToState = currentState;
}

void GameStateManager::SwitchState( GameState newState )
{
	switch(newState)
	{
	case GAME:
		currentState = GAME;
		log << WARN << "Switching to Game state" << std::endl;
		if(!gameWasInited)
		{
			input.resize(window_width, window_height, true);
			DisplayLoadingScreen();
			input.resize(window_width, window_height);
			game->InitGamePlayManager(&input, &switchToState);
			gameWasInited = true;
		}
		game->OnEnteringGameState();
		break;
	case MAIN_MENU:
		currentState = MAIN_MENU;
		log << WARN << "Switching to Menu state" << std::endl;
		if(!menuWasInited)
		{
			input.resize(window_width, window_height, true);
			DisplayLoadingScreen();
			input.resize(window_width, window_height);

			mainMenu->Init(&input, &switchToState);
			menuWasInited = true;
		}
		mainMenu->OnEnteringMenu();
		break;
	case OPTIONS:
		log << WARN << "Switching to Options state" << std::endl;
		if(!optionsWasInited)
		{
			input.resize(window_width, window_height, true);
			DisplayLoadingScreen();
			input.resize(window_width, window_height);

			options->Init(&input, &switchToState);
			optionsWasInited = true;
		}
		options->SetBackState(currentState);
		options->OnEnteringMenu();
		currentState = OPTIONS;
		break;
	case INGAME_MENU:
		currentState = INGAME_MENU;
		log << WARN << "Switching to Ingame Menu state" << std::endl;
		if(!ingameMenuWasInited)
		{
			input.resize(window_width, window_height, true);
			DisplayLoadingScreen();
			input.resize(window_width, window_height);
			ingameMenu->Init(&input, &switchToState);
			ingameMenuWasInited = true;
		}
		ingameMenu->OnEnteringMenu();
		break;
	case NEW_GAME:
		currentState = newState;
		if(!gameWasInited)
		{
			input.resize(window_width, window_height, true);
			DisplayLoadingScreen();
			input.resize(window_width, window_height);
			game->InitGamePlayManager(&input, &switchToState);
			gameWasInited = true;
		}
		game->ResetGame();
		//SwitchState(GAME);
		switchToState = GAME;
		break;
	case QUIT:
		exit = true;
		break;
	}
}

void GameStateManager::GameLoop()
{
	float fps = 0.0f;
	float fpsTimer = 0.0f;
	while(!exit)
	{
		if(switchToState != currentState)
		{
			SwitchState(switchToState);
		}
		deltaTime = static_cast<float>(timer.elapsedAndRestart());
		fpsTimer += deltaTime;
		
		if(fpsTimer >= 0.3f)//updating the fps counter once every second
		{
			fps = 1/deltaTime;
			std::ostringstream captionStream;
			captionStream << "FPS: " << fps;
			SDL_WM_SetCaption(captionStream.str().c_str(), "");
			fps = 0;
			fpsTimer = 0;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		input.Update(&switchToState);
		
		HandleInput();
		
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
		game->Update(deltaTime);
		break;
	case MAIN_MENU:
		mainMenu->UpdateMenu(deltaTime);
		break;
	case OPTIONS:
		options->UpdateMenu(deltaTime);
		break;
	case INGAME_MENU:
		ingameMenu->UpdateMenu(deltaTime);
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
	case MAIN_MENU:
		mainMenu->RenderMenu();
		break;
	case OPTIONS:
		options->RenderMenu();
		break;
	case INGAME_MENU:
		ingameMenu->RenderMenu();
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
	glScalef(2, 2, 2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);

	Texturable texturable;
	texturable.InitTexture("..//images//LoadingScreen.jpg", "loadingscreen");
	texturable.BindTexture("loadingscreen");


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
	glPopMatrix();
}

void GameStateManager::HandleInput()
{
	if(input.KeyDownOnce(SDLK_ESCAPE))
	{
		switch(currentState)
		{
		case GAME_OVER:
			switchToState = MAIN_MENU;
			break;
		case OPTIONS:
			switchToState = MAIN_MENU;
			break;
		case INGAME_MENU:
			switchToState = GAME;
			break;
		case MAIN_MENU:
			switchToState = QUIT;
			break;
		case GAME:
			switchToState = INGAME_MENU;
			break;
		}
	}
}
