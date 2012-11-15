/********************************************************************
    created:    7:10:2012   15:11
    filename:   AiStateMachine.h
    author:     Kristian Skarseth
    
    purpose:    Our AI state machine. It handles updaing of current state(s)
				and the change from one state to another
*********************************************************************/
#ifndef AiStateMachine_h__
#define AiStateMachine_h__

#include "AiState.h"
#include "BaseEnemyShip.h"


class AiStateMachine
{
public:
	//Ctor for the state machine. The state machine needs a pointer to the class
	//that owns it (param 1), an AiState ptr to the state we wish to start in
	//(param 2) and another AiState ptr to the state we wish to always be active.
	//The ptrs are of type shared_ptr<AiState>
	AiStateMachine(BaseEnemyShip* owner, 
		std::shared_ptr<AiState> startupState, 
		std::shared_ptr<AiState> constantState)
	{
		this->owner = owner;

		this->constantState = constantState;
		this->constantState->Enter(this->owner);

		this->currentState = startupState;		
		this->currentState->Enter(this->owner);
	}

	//Calls UpdateState() on the constant and current states.
	void Update(GLfloat deltaTime)
	{
		this->constantState->UpdateState(owner, deltaTime);
		this->currentState->UpdateState(owner, deltaTime);
	}

	//Changes the currentState to the param newState. Exit() will
	//be called on the old currentState before the switch is made,
	//and then Enter() will be called on the newState
	void ChangeState(std::shared_ptr<AiState> newState)
	{
		currentState->Exit(owner);
		currentState = newState;
		currentState->Enter(owner);
	}

	std::string GetCurrentState()
	{
		return currentState->GetStateIdentifier();
	}
private:
	//A local reference to the class that owns this stateMachine
	BaseEnemyShip* owner;

	//A sharedPtr to the current AiState
	std::shared_ptr<AiState> currentState;

	//A sharedPtr to the constant AiState. This 
	//state is always used regardless of the currentState
	std::shared_ptr<AiState> constantState;
};

#endif // AiStateMachine_h__