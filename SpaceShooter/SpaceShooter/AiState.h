/********************************************************************
    created:    7:10:2012   15:06
    filename:   AiState.h
    author:     Kristian Skarseth
    
    purpose:    Abstract base class for all AI States. All AI states has to overwrite
				all the functions in this class.
				
				Enter() is called when we enter this state
				Execute() is called each game update when this state is active
				Exit() is called when we leave this state
*********************************************************************/
#ifndef AiState_h__
#define AiState_h__
#include <Windows.h>
#include <gl/glew.h>
#include <string>

class BaseEnemyShip;

class AiState
{
public:
	AiState(std::string identifier){StateIdentifier = identifier;}
	virtual ~AiState(){}

	//Function called when we enter this state
	virtual void Enter(BaseEnemyShip* owner) = 0;

	//Function called each update when this state is active
	virtual void UpdateState(BaseEnemyShip* owner, GLfloat deltaTime) = 0;

	//Function called when switching out from this tate
	virtual void Exit(BaseEnemyShip* owner) = 0;

	//Returns an identifier for the state type
	std::string GetStateIdentifier(){return StateIdentifier;}

protected:
	std::string StateIdentifier;

};

#endif // AiState_h__