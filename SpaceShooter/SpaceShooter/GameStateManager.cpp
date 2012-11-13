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
	SetOpenGLVideoMode();

	InitGlew();
	InitDevil();

	texturable.InitTexture("..//images//LoadingScreen.jpg", "loadingscreen");
	vbo.SetMeshInfo(MeshFactory::Inst()->GetMesh("..//xml//square.xml"));

	DisplayLoadingScreen();
	SoundManager::Inst()->InitSoundManager();
	SoundManager::Inst()->PlaySong("imperial_probe");
	input.InitInputManager();
	TextFactory::Inst()->InitTextFactory();
	

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
	prevState = currentState;
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
		mainMenu->OnEnteringMenu(&prevState);
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
		options->OnEnteringMenu(&prevState);
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
		ingameMenu->OnEnteringMenu(&prevState);
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
		
		if(fpsTimer >= 0.3f)//updating the fps counter once every .3sec
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
		SoundManager::Inst()->Update(deltaTime);
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
void GameStateManager::PlayIntroVideo()
{
	SetSDLVideoMode();
	input.InitInputManager();
	std::shared_ptr<SmpegPlayer> vidPlayer = std::make_shared<SmpegPlayer>();
	vidPlayer->Load("..//Video//intro.mpg", screen);
	vidPlayer->Play();
	while(vidPlayer->GetStatus() == SMPEG_PLAYING)
	{
		SDL_FillRect( screen, 0, 0 );
		vidPlayer->Display();
		input.Update(&switchToState);
		if(input.KeyDownOnce(SDLK_ESCAPE))
		{
			vidPlayer->Stop();
		}
		SDL_Flip(screen);
	}
	
	//ugly hack to avoid getting some small white borders after playing video
	screen = SDL_SetVideoMode(
		1279,						//Window Width
		719,						//Window Height
		16,								//Bit depth
		SDL_HWSURFACE | SDL_DOUBLEBUF);	//Flag
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
	glScaled(2, 2, 2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);

	texturable.BindTexture("loadingscreen");
	vbo.Draw();
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
			switchToState = prevState;
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

void GameStateManager::SetOpenGLVideoMode()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::stringstream err;
		err << "Could not initialize SDL: " << SDL_GetError();
		throw std::runtime_error(err.str());
	}
	atexit( SDL_Quit);


	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Use double buffering
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); // Use framebuffer with 16 bit depth buffer
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Use framebuffer with 8 bit for red
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // Use framebuffer with 8 bit for green
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // Use framebuffer with 8 bit for blue
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Use framebuffer with 8 bit for alpha

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	screen = SDL_SetVideoMode(window_width, window_height, 0, SDL_OPENGL 
		| SDL_DOUBLEBUF | SDL_RESIZABLE);
	if(screen == NULL) 
	{
		std::stringstream err;
		err << "SDL_SetVideoMode failed ";
		throw std::runtime_error(err.str());
	}

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapBuffers();
}

void GameStateManager::SetSDLVideoMode()
{
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		if (0 > SDL_Init(SDL_INIT_EVERYTHING))
		{
			log << CRITICAL << "Cannot Initialize SDL video Subsystem - " << SDL_GetError() << endl;
		}
		else
		{
			screen = SDL_SetVideoMode(
				1280,						//Window Width
				720,						//Window Height
				16,								//Bit depth
				SDL_HWSURFACE | SDL_DOUBLEBUF);	//Flags

			if (!screen) 
			{
				log << CRITICAL << "Cannot set video mode - " << SDL_GetError() << endl;
			}
		}
	}
}
