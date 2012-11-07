/********************************************************************
	created:	1:10:2012   14:02
	filename: 	InputManager.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef InputManager_h__
#define InputManager_h__

#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/GLU.h>
#include <SDL.h>

#include "GameConstants.h"
class InputManager
{
public:
	InputManager(); //ctor
	~InputManager();//dtor

	//Handles updates the input manager relies on to do input checks.
	//Should be called in the beginning of each game loop update
	//param bool should be a ref to the bool running the gameloop
	void Update(bool& exitGame);

	//Returns true if the param key is down, try to avoid
	//using this function, rely on the predefined game-
	//specific functions instead.
	bool KeyDownHold(SDLKey key);
	
	//Returning true when the game should be quit (escape or 'q')
	bool Quit();

	//Returning true if left mouse btn is being held down
	bool LeftMouseDownHold();

	//Returning true if middle mouse btn is being held down
	bool MiddleMouseDownHold();

	//Returning true if right mouse btn is being held down
	bool RightMouseDownHold();

	bool LeftMouseDownOnce(){return leftDownOnce;}
	bool RightMouseDownOnce(){return rightDownOnce;}
	bool MiddleMouseDownOnce(){return middleDownOnce;}

	//Returning true if fire button is held down (space)
	bool Fire();

	//Returning true if move left button is held down
	bool MoveLeft();

	//Returning true if Move right button is held down
	bool MoveRight();

	//Returning true if move up button is held down
	bool MoveUp();

	//Returning true if move down button is held down
	bool MoveDown();

	void resize(unsigned int width, unsigned int height);

private:
	Uint8* keystates;	// Holds a snapshot of keys on the keyboard.

	bool leftDownOnce, middleDownOnce, rightDownOnce;
	Uint8 mouseBtns;	// Holds a snapshot of the mouse buttons' state
	int mouseX;		// Mouse x pos	
	int mouseY;		// Mouse y pos
};

#endif // InputManager_h__
