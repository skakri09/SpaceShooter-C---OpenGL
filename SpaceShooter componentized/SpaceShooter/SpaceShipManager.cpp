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
	//Its not nessescary to load the player ship, as it's always loaded on the start
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialTieFighter//ImperialTieFighter.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//SithInfiltrator//SithInfiltrator.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialTieInterceptor//ImperialTieInterceptor.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialStarDestroyer//ImperialStarDestroyer.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//Planets//Endor//Endor.3ds");
	planet.CreatePlanet("Endor//Endor.3ds");
	player.InitSpaceShip(0.0f, -10.0f, 0.0f, 0, 0, 0, 0, 0, 0, -1);

	EnemySpaceShips.push_back(GetRandomEnemy());
	for(auto i = EnemySpaceShips.begin(); i != EnemySpaceShips.end(); i++)
	{
		//float x = GetRandFloat(-100.0f, 100.0f);
		//float y = GetRandFloat(-50.0f, 50.0f);
		//float z = GetRandFloat(-500.0f, -400.0f);
		float x = -175; float y = 0; float z = -440;
		EnemySpaceShips.back()->InitSpaceShip(x, y, z, -90, 1, 0, 0, 0, 0, 1);
	}
	TimeSinceLastEnemySpawn = 0.0f;
	EnemySpaceShips.push_back(std::make_shared<ImperialStarDestroyer>(&player));
	EnemySpaceShips.back()->InitSpaceShip(-200, 200, -600, 200, 0, 1, 0, 0, 0, 1);
}

void SpaceShipManager::UpdateManager(GLfloat deltaTime)
{
	planet.Update(deltaTime);

	if(input->Fire())
	{
		player.Shoot();
	}
	HandlePlayerRotation();
	HandleXAxisMovement();
	HandleYAxisMovement();
	
	HandleFrustumCollision();

	if(!player.CanKill())
	{
		player.Update(deltaTime);
	}
	else
	{

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
		}
		else
		{
			(*i)->Update(deltaTime);
			if(!player.CanKill())
			{
				(*i)->HandleProjectileCollision(player.GetProjectiles());
				player.HandleProjectileCollision( (*i)->GetProjectiles());
			}
			++i;
		}
	}
	TimeSinceLastEnemySpawn += deltaTime;
	if(TimeSinceLastEnemySpawn >= 1.01)
	{
		/*TimeSinceLastEnemySpawn = 0.0f;
		EnemySpaceShips.push_back(GetRandomEnemy());
		float x = GetRandFloat(-100.0f, 100.0f);
		float y = GetRandFloat(-50.0f, 50.0f);
		float z = GetRandFloat(-500.0f, -400.0f);
		EnemySpaceShips.back()->InitSpaceShip(x, y, z, -90, 1, 0, 0, 0, 0, 1);*/
	}
}

void SpaceShipManager::DrawSpaceShips()
{
	
	glPushMatrix();
	
	planet.Draw();

	player.Draw();
	
	for(auto i = EnemySpaceShips.begin(); i != EnemySpaceShips.end();i++)
	{
		(*i)->Draw();
	}

	glPopMatrix();
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

std::shared_ptr<BaseEnemyShip> SpaceShipManager::GetRandomEnemy()
{
	float random = GetRandFloat(0.0f, 3.0f);
	
	if(random >=0 && random <= 1.0f)
	{
		return std::make_shared<ImperialTieFighter>(&player);
	}
	else if(random > 1 && random <= 2.0f)
	{
		return std::make_shared<ImperialTieInterceptor>(&player);
	}
	else if(random > 2 && random <= 3.0f)
	{
		return std::make_shared<SithInfiltrator>(&player);
	}
	return NULL;
}

void SpaceShipManager::TransferShipToShipManager( std::shared_ptr<BaseEnemyShip> ship )
{
	EnemyShipsForTransfer.push_back(ship);
}

PlayerSpaceShip* SpaceShipManager::GetPlayer()
{
	return &player;
}
