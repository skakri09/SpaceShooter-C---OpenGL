//#include "GamePlayManager.h"
#include "GameStateManager.h"
#include <iostream>
#include "Logger.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl/glew.h>
/**
 * Simple program that starts our game manager
 */
int main(int argc, char *argv[]) 
{
	Logger log("main", INFO);
	log << INFO << "Starting Game" << std::endl;

	try 
	{
		GameStateManager* stateManager;
		stateManager = new GameStateManager();
		//stateManager->PlayIntroVideo();
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
