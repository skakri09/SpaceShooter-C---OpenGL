#include "InputManager.h"


InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::InitInputManager()
{
	leftDownOnce = false;
	rightDownOnce = false;
	middleDownOnce = false;

	keystates = SDL_GetKeyState(&keyCount);
	prevKeystates = new Uint8[keyCount];

	activeWidth = window_width;
	activeHeight = window_height;

	//Call pump event twice to flush any previous inputs
	SDL_PumpEvents();
	SDL_PumpEvents();
}


void InputManager::Update(GameState* gameState)
{
	mouseBtns = SDL_GetMouseState(&mouseX, &mouseY);

	memcpy(prevKeystates, keystates, sizeof(Uint8) * keyCount);

	SDL_PumpEvents();

	leftDownOnce = false;
	rightDownOnce = false;
	middleDownOnce = false;
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) 
			{
			case SDLK_ESCAPE:
				if(*gameState == MENU)
				{
					*gameState = QUIT;
				}
				else
				{
					*gameState = MENU;
				}
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
				switch(event.button.button)
				{
				case SDL_BUTTON_LEFT:
					leftDownOnce = true;
					break;
				case SDL_BUTTON_RIGHT:
					rightDownOnce = true;
					break;
				case SDL_BUTTON_MIDDLE:
					middleDownOnce = true;
					break;
				}
			}
			break;
		case SDL_QUIT: //e.g., user clicks the upper right x
			*gameState = QUIT;
			break;
		case SDL_VIDEORESIZE:
			activeWidth = event.resize.w;
			activeHeight = event.resize.h;
			resize(activeWidth, activeHeight);
			break; 
		}
		if(event.button.button == SDL_BUTTON_WHEELDOWN)
		{
		}
		else if(event.button.button == SDL_BUTTON_WHEELUP)
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

bool InputManager::KeyDownOnce( SDLKey key )
{
	if(keystates[key] != NULL && prevKeystates[key] == NULL) 
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

void InputManager::resize( unsigned int width, unsigned int height, bool toDefault)
{
	if(!toDefault)
	{
		glViewport(0, 0, activeWidth, activeHeight);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(75.0f, 1.7f, 1, FRUSTUM_DEPTH);
		//gluLookAt(0, 1.10, CAMERA_POS,	0, 0.3, 0,	0, 1, 0); 
		//gluLookAt(0.0f, 20.0f, 20.0f, 0.0f, 0.0f ,-13.0f, 0.0f, 1.0f, 0.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else
	{
		glViewport(0, 0, activeWidth, activeHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, 1, -1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

bool InputManager::Fire()
{
	if(keystates[SDLK_SPACE] != NULL)
	{
		return true;
	}
	return false;
}

