/********************************************************************
    created:    9:11:2012   21:13
    filename:   GameStateManager.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef GameStateManager_h__
#define GameStateManager_h__

#include "GameState.h"

class GameStateManager
{
public:
    GameStateManager();
    ~GameStateManager();

	void SwitchState(GameState newState);


private:
	void OnSwitchToGameState();
	void OnSwitchToMenuState();
};

#endif // GameStateManager_h__