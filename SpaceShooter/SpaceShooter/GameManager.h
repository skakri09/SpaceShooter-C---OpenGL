#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <memory>
#include <SDL.h>


#include "Timer.h"
#include "Drawable.h"
#include "PlayerSpaceShip.h"
#include "Projectile.h"

#include <gl/gl.h>

/**
 * This class handles the game logic and display.
 * Uses SDL as the display manager, and glm for 
 * vector and matrix computations
 */

static const float PLAYER_X_VELOCITY = 50.0f;
static const float PLAYER_Y_VELOCITY = 50.0f;
static const float PLAYER_Z_VELOCITY = 100.0f;
static const float FRUSTUM_LEFT = -55.0f;
static const float FRUSTUM_RIGHT = 55.0f;
static const float FRUSTUM_TOP = 46.0f;
static const float FRUSTUM_BOTTOM = -28.0f;

class GameManager 
{
public:

	/**
	 * Constructor
	 */
	GameManager();

	/**
	 * Destructor
	 */
	~GameManager();

	/**
	 * Initializes the game, including the OpenGL context
	 * and data required
	 */
	void init();

	/**
	 * The main loop of the game. Runs the SDL main loop
	 */
	void play();

	/**
	 * Quit function
	 */
	void quit();

	/**
	 * Function that handles rendering into the OpenGL context
	 */
	void render();

	/**
	  * Function that is called when the window is resized
	  */
	void resize(unsigned int width, unsigned int height);

protected:
	/**
	 * Creates the OpenGL context using SDL
	 */
	void createOpenGLContext();

	/**
	 * Sets states for OpenGL that we want to keep persistent
	 * throughout the game
	 */
	void setOpenGLStates();

	static const unsigned int window_width = 800;
	static const unsigned int window_height = 600;

private:
	Logger log;
	Timer my_timer;		//Timer for machine independent motion
	GLfloat deltaTime;	//Time since last update 
	
	//Returns true if the param key is down
	bool keyDown(SDLKey key);
	
	//Handles movement along the x axis. Checks for input and changes
	//x velocity based on the input.
	void HandleXAxisMovement();
	//Handles movement along the y axis. Checks for input and changes
	//y velocity based on the input.
	void HandleYAxisMovement();
	
	//Does simple collision checking with the frustum. The truth is it
	//only checks for collision against set x and y coordinates that 
	//matches the sides of the screen where the ship starts. If its
	//moved somewhere along the z axis, it wont check against the 
	//frustum, but against an invisible wall matching the coordinates.
	void HandleFrustumCollision();

	Uint8* keystates; // Holds a snapshot of keys on the keyboard.

	CPlayerSpaceShip player; // Player spaceship object
};

#endif // _GAMEMANAGER_H_
