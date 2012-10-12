#include "SpaceShipManager.h"


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

	player.InitSpaceship(0.0f, -10.0f, 0.0f, 0, 0, 0, 0, 0, 0, -1);

	EnemySpaceShips.push_back(std::make_shared<ImperialTieInterceptor>(&player));
	for(auto i = EnemySpaceShips.begin(); i != EnemySpaceShips.end(); i++)
	{
		(*i)->InitSpaceship(100.0f, 0.0f, -50.0f, -90, 1, 0, 0, 0, 0, 1);
	}
}

void SpaceShipManager::UpdateManager(GLfloat deltaTime)
{
	if(input->Fire())
	{
		player.Shoot();
	}
	HandlePlayerRotation();
	HandleXAxisMovement();
	HandleYAxisMovement();
	
	HandleFrustumCollision();

	if(player.GameObjectAlive())
	{
		player.Update(deltaTime);
	}
	

	for(auto i = EnemySpaceShips.begin(); i != EnemySpaceShips.end();)
	{
		if( !(*i)->GameObjectAlive() )
		{
			i = EnemySpaceShips.erase(i);
		}
		else
		{
			(*i)->Update(deltaTime);
			(*i)->HandleProjectileCollision(player.GetProjectiles());
			player.HandleProjectileCollision( (*i)->GetProjectiles());
			++i;
		}
	}
	if(EnemySpaceShips.size() == 0)
	{
		EnemySpaceShips.push_back(std::make_shared<SithInfiltrator>(&player));
		EnemySpaceShips.back()->InitSpaceship(100.0f, 0.0f, -50.0f, -90, 1, 0, 0, 0, 0, 1);
	}

	/*if(player.HandleProjectileCollision(enemy.GetProjectiles()))
	{
  		log << WARN << "Player was hit by a projectile!" << std::endl;
	}*/
	//player.GetCollisionSphere()->IsCollision(enemy.GetCollisionSphere());
	
}

void SpaceShipManager::DrawSpaceShips()
{
	if(player.GameObjectAlive())
	{
		player.Draw();
	}
	
	for(auto i = EnemySpaceShips.begin(); i != EnemySpaceShips.end();i++)
	{
		if( (*i)->GameObjectAlive() )
		{
			(*i)->Draw();
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

void SpaceShipManager::HandlePlayerRotation()
{
	if(input->LeftMouseDownOnce())
	{
		player.InitRotation(Y_AXIS);
	}
}
