#include "InputManager.h"


InputManager::InputManager()
{
}

InputManager::~InputManager()
{

}

void InputManager::Update(bool& exitGame)
{
	mouseBtns = SDL_GetMouseState(&mouseX, &mouseY);

	keystates = SDL_GetKeyState(NULL);
	
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) 
			{
			case SDLK_ESCAPE:
				exitGame = true;
				break;
			case SDLK_q:
				exitGame = true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
				switch(event.button.button)
				{
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				case SDL_BUTTON_MIDDLE:
					break;
				}
			}
			break;
		case SDL_QUIT: //e.g., user clicks the upper right x
			exitGame = true;
			break;
		case SDL_VIDEORESIZE:
			resize(event.resize.w, event.resize.h);
			break; 
		}
		if(event.button.button == SDL_BUTTON_WHEELDOWN)
		{
		}
		else if(event.button.button == SDL_BUTTON_WHEELUP)
		{
		}
		else
		{
		}
	}
}

bool InputManager::KeyDownHold( SDLKey key )
{
	if(keystates[key] != NULL)
	{
		return true;
	}
	return false;
}

bool InputManager::LeftMouseDownHold()
{
	return ((mouseBtns&SDL_BUTTON_LEFT) != 0);
}

bool InputManager::MiddleMouseDownHold()
{
	return ((mouseBtns&SDL_BUTTON_MIDDLE) != 0);
}

bool InputManager::RightMouseDownHold()
{
	return ((mouseBtns&SDL_BUTTON_RIGHT) != 0);
}

bool InputManager::MoveLeft()
{
	if(keystates[SDLK_LEFT] != NULL
		|| keystates[SDLK_a] != NULL)
	{
		return true;
	}
	return false;
}

bool InputManager::MoveRight()
{
	if(keystates[SDLK_RIGHT] != NULL
		|| keystates[SDLK_d] != NULL)
	{
		return true;
	}
	return false;
}

bool InputManager::MoveUp()
{
	if(keystates[SDLK_UP] != NULL
		|| keystates[SDLK_w] != NULL)
	{
		return true;
	}
	return false;
}

bool InputManager::MoveDown()
{
	if(keystates[SDLK_DOWN] != NULL
		|| keystates[SDLK_s] != NULL)
	{
		return true;
	}
	return false;
}

void InputManager::resize( unsigned int width, unsigned int height )
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.5f, 1.0f, 600.0f);
	gluLookAt(0, 1.10, 30,	0, 0.30, 0,		0, 1, 0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool InputManager::Fire()
{
	if(keystates[SDLK_SPACE] != NULL)
	{
		return true;
	}
	return false;
}
