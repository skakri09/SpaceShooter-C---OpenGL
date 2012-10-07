/********************************************************************
    created:    7:10:2012   15:06
    filename:   AiState.h
    author:     Kristian Skarseth
    
    purpose:    Template class for an AI state. Holds the 3 pure virtual
				functions that an AI state uses. Each AI state implementation
				overwrites the functions to do what the particular AI behavior
				wants done.
				
				Enter() is called when we enter this state
				Execute() is called each game update when this state is active
				Exit() is called when we leave this state
*********************************************************************/
#ifndef AiState_h__
#define AiState_h__
#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <string>

class BaseEnemyShip;

class AiState
{
public:
	AiState(std::string identifier){StateIdentifier = identifier;}
	virtual ~AiState(){}

	virtual void Enter(BaseEnemyShip* owner){}
	virtual void UpdateState(BaseEnemyShip* owner, GLfloat deltaTime){}
	virtual void Exit(BaseEnemyShip* owner){}

	std::string GetStateIdentifier(){return StateIdentifier;}
protected:
	std::string StateIdentifier;

};

#endif // AiState_h__