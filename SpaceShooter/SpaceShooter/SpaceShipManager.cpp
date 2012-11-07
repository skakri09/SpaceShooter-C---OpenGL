#include "SpaceShipManager.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;


SpaceShipManager* SpaceShipManager::Inst()
{
	static SpaceShipManager* instance = new SpaceShipManager();
	return instance;
}

SpaceShipManager::SpaceShipManager() 
	:log("SpaceShipmanager", WARN)
{
}

SpaceShipManager::~SpaceShipManager()
{
}

void SpaceShipManager::InitManager(InputManager* input)
{
	this->input = input;
	
	//making sure to pre-load all spaceships we will be using so we dont have to do it on runtime
	//Its not necessary to load the player ship, as it's always loaded on the start
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialTieFighter//ImperialTieFighter.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialTieInterceptor//ImperialTieInterceptor.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialStarDestroyer//ImperialStarDestroyer.3ds");

	
	player.InitSpaceShip(0.0f, -10.0f, 0.0f, 0, 0, 0, 0, 0, 0, -1);
	EnemySpaceShips.push_back(std::make_shared<ImperialStarDestroyer>(&player));
	EnemySpaceShips.back()->InitSpaceShip(-200, 200, -600, 200, 0, 1, 0, 0, 0, 1);
}

void SpaceShipManager::UpdateManager(GLfloat deltaTime, bool& exit)
{
	if(input->Fire())
	{
		player.Shoot(LASER_FAST);
	}
	HandlePlayerRotation();
	HandleXAxisMovement();
	HandleYAxisMovement();
	
	HandleFrustumCollision();

	player.Update(deltaTime);
	if(player.CanKill())
	{
		exit = true;
	}

	for(auto i = EnemyShipsForTransfer.begin(); i != EnemyShipsForTransfer.end();)
	{
		EnemySpaceShips.push_back(*i);
		i = EnemyShipsForTransfer.erase(i);
	}

	for(auto i = EnemySpaceShips.begin(); i != EnemySpaceShips.end();)
	{
		if( (*i)->CanKill() )
		{
			i = EnemySpaceShips.erase(i);
			log << WARN << "killing spaceship" << std::endl;
		}
		else
		{
			(*i)->Update(deltaTime);
			++i;
		}
	}
	HandleCollision();
}

void SpaceShipManager::DrawSpaceShips()
{
	glPushMatrix();

	player.Draw();
	
	for(auto i = EnemySpaceShips.begin(); i != EnemySpaceShips.end();i++)
	{
		(*i)->Draw();
	}

	glPopMatrix();
}

void SpaceShipManager::TransferShipToShipManager( std::shared_ptr<BaseEnemyShip> ship )
{
	EnemyShipsForTransfer.push_back(ship);
}

PlayerSpaceShip* SpaceShipManager::GetPlayer()
{
	return &player;
}

std::vector<std::shared_ptr<BaseEnemyShip>>* SpaceShipManager::GetEnemySpaceships()
{
	return &EnemySpaceShips;
}

//  P R I V A T E    F U N C T I O N S  //
//**************************************//

void SpaceShipManager::HandleCollision()
{
	std::vector<std::shared_ptr<Projectile>>* projectiles = 
		ProjectileManager::Inst()->GetProjectiles();
	for(auto i = projectiles->begin(); i != projectiles->end(); i++)
	{
		if( *(*i)->GetOwner() == player )
		{
			for(auto s = EnemySpaceShips.begin(); s != EnemySpaceShips.end(); s++)
			{
				(*s)->HandleProjectileCollision( (*i) );
			}
		}
		else
		{
			player.HandleProjectileCollision( (*i) );
		}
	}
}

void SpaceShipManager::HandleXAxisMovement()
{
	if (input->MoveLeft()|| input->MoveRight())
	{
		//if left and right
		if (input->MoveLeft() && input->MoveRight())
		{
			player.transformable.setXVel(0.0f);
		}
		//If only left
		if (input->MoveLeft() && !input->MoveRight())
		{
			player.transformable.setXVel(-PLAYER_XY_VELOCITY);
		}
		//If only right
		if (!input->MoveLeft() && input->MoveRight())
		{
			player.transformable.setXVel(PLAYER_XY_VELOCITY);
		}
	}
	else
	{
		//No movement
		player.transformable.setXVel(0.0f);
	}
}

void SpaceShipManager::HandleYAxisMovement()
{
	if (input->MoveUp()|| input->MoveDown())
	{
		//if up and down
		if (input->MoveUp() && input->MoveDown())
		{
			player.transformable.setYVel(0.0f);
		}
		//If only up
		if (input->MoveUp() && !input->MoveDown())
		{
			player.transformable.setYVel(PLAYER_XY_VELOCITY);
		}
		//If only down
		if (!input->MoveUp() && input->MoveDown())
		{
			player.transformable.setYVel(-PLAYER_XY_VELOCITY);
		}
	}
	else
	{
		//No movement
		player.transformable.setYVel(0.0f);
	}
}

void SpaceShipManager::HandleFrustumCollision()
{
	if( (player.transformable.getXPos() >= FRUSTUM_RIGHT && player.transformable.getXVel() > 0.0f) || 
		(player.transformable.getXPos() <= FRUSTUM_LEFT && player.transformable.getXVel() < 0.0f))
	{
		player.transformable.setXVel(0.0f);
	}
	if( (player.transformable.getYPos() >= FRUSTUM_TOP && player.transformable.getYVel() > 0.0f) || 
		(player.transformable.getYPos() <= FRUSTUM_BOTTOM && player.transformable.getYVel() < 0.0f))
	{
		player.transformable.setYVel(0.0f);
	}
	log << INFO << player.transformable.getYPos() << std::endl;
}

void SpaceShipManager::HandlePlayerRotation()
{
	/*if(input->LeftMouseDownOnce())
	{
		player.InitRotation(Y_AXIS);
	}*/
}