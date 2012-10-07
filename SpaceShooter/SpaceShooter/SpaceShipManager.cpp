#include "SpaceShipManager.h"


SpaceShipManager::SpaceShipManager() 
	:log("SpaceShipmanager", WARN),
	enemy(&player)
{
}

SpaceShipManager::~SpaceShipManager()
{
}

void SpaceShipManager::InitManager(InputManager* input)
{
	this->input = input;

	player.InitSpaceship(0.0f, 0.0f, 0.0f);
	enemy.InitSpaceship(0.0f, 0.0f, -100.0f);
}

void SpaceShipManager::UpdateManager(GLfloat deltaTime)
{
	if(input->Fire())
	{
		player.Shoot();
	}

	HandleXAxisMovement();
	HandleYAxisMovement();
	
	HandleFrustumCollision();

	player.Update(deltaTime);
	enemy.Update(deltaTime);
	
}

void SpaceShipManager::DrawSpaceShips()
{
	player.Draw();
	enemy.Draw();
}

void SpaceShipManager::HandleXAxisMovement()
{
	if (input->MoveLeft()|| input->MoveRight())
	{
		//if left and right
		if (input->MoveLeft() && input->MoveRight())
		{
			player.setXVel(0.0f);
		}
		//If only left
		if (input->MoveLeft() && !input->MoveRight())
		{
			player.setXVel(-PLAYER_X_VELOCITY);
		}
		//If only right
		if (!input->MoveLeft() && input->MoveRight())
		{
			player.setXVel(PLAYER_X_VELOCITY);
		}
	}
	else
	{
		//No movement
		player.setXVel(0.0f);
	}
}

void SpaceShipManager::HandleYAxisMovement()
{
	if (input->MoveUp()|| input->MoveDown())
	{
		//if up and down
		if (input->MoveUp() && input->MoveDown())
		{
			player.setYVel(0.0f);
		}
		//If only up
		if (input->MoveUp() && !input->MoveDown())
		{
			player.setYVel(PLAYER_Y_VELOCITY);
		}
		//If only down
		if (!input->MoveUp() && input->MoveDown())
		{
			player.setYVel(-PLAYER_Y_VELOCITY);
		}
	}
	else
	{
		//No movement
		player.setYVel(0.0f);
	}
}

void SpaceShipManager::HandleFrustumCollision()
{
	if( (player.getXPos() >= FRUSTUM_RIGHT && player.getXVel() > 0.0f) || 
		(player.getXPos() <= FRUSTUM_LEFT && player.getXVel() < 0.0f))
	{
		player.setXVel(0.0f);
	}
	if( (player.getYPos() >= FRUSTUM_TOP && player.getYVel() > 0.0f) || 
		(player.getYPos() <= FRUSTUM_BOTTOM && player.getYVel() < 0.0f))
	{
		player.setYVel(0.0f);
	}
	log << INFO << player.getYPos() << std::endl;
}
