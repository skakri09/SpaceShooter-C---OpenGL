//#include "GameManager.h"
#include "GameStateManager.h"
#include <iostream>
#include "Logger.h"
#ifdef _WIN32
#include <Windows.h>
#endif

/**
 * Simple program that starts our game manager
 */
int main(int argc, char *argv[]) 
{
	Logger log("main", INFO);
	log << INFO << "Starting Game" << std::endl;

	try 
	{
		/*GameManager* game;
		game = new GameManager();
		game->init();
		game->GameLoop();
		delete game;*/
		GameStateManager* stateManager;
		stateManager = new GameStateManager();
		stateManager->InitGameStateManager();
		stateManager->GameLoop();
		delete stateManager;
		stateManager = 0;

	} 
	catch (std::exception &e) 
	{
		std::string err = e.what();
		std::cout << err.c_str() << std::endl;
		system("pause");
		return -1;
	}
	return 0;
}
