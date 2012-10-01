#include "InputManager.h"


InputManager::InputManager()
{
	doExit = false;
}

InputManager::~InputManager()
{

}

void InputManager::Update()
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
				doExit = true;
				break;
			case SDLK_q:
				doExit = true;
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
			doExit = true;
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
	return(keystates[key]);
}

bool InputManager::Quit()
{
	return doExit;	
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

bool InputManager::SpaceBtnDown()
{
	return(keystates[SDLK_SPACE]);
}

bool InputManager::MoveLeft()
{
	return(keystates[SDLK_LEFT]);
}

bool InputManager::MoveRight()
{
	return(keystates[SDLK_RIGHT]);
}

bool InputManager::MoveUp()
{
	return(keystates[SDLK_UP]);
}

bool InputManager::MoveDown()
{
	return(keystates[SDLK_DOWN]);
}

void InputManager::resize( unsigned int width, unsigned int height )
{
	/*glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, 1.5f, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}
