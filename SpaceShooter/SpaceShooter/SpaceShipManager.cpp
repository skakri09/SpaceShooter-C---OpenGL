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

void SpaceShipManager::InitManager(InputManager* input, GameState* gameState, ScoreManager* scoreManager)
{
	this->scoreManager = scoreManager;
	this->input = input;
	this->gameState = gameState;

	//making sure to pre-load all spaceships we will be using so we dont have to do it on runtime
	//Its not necessary to load the player ship, as it's always loaded on the start
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialTieFighter//ImperialTieFighter.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialTieInterceptor//ImperialTieInterceptor.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//ImperialStarDestroyer//ImperialStarDestroyer.3ds");
	MeshFactory::Inst()->LoadMesh("..//3ds//MilleniumFalcon//MilleniumFalcon.3ds");
	ResetSpaceships();
}

void SpaceShipManager::Update(GLfloat deltaTime)
{
	if(input->Fire())
	{
		if(player->Shoot(DOUBLE_TRIPLE_CONE_LASER))
		{
			SoundManager::Inst()->PlayEffect("laser_tripleFire_long", 40);
		}
	}

	HandlePlayerRotation();
	HandleXAxisMovement();
	HandleYAxisMovement();
	
	HandleFrustumCollision();

	player->Update(deltaTime);

	if(player->CanKill())
	{
		*gameState = MAIN_MENU;
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
			if( (*i)->WasKilledByPlayer())
			{
				scoreManager->EnemyKilled((*i)->GetEnemyType());
			}
			
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

	player->Draw();
	
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

void SpaceShipManager::TransferShipToShipManager( std::shared_ptr<PlayerSpaceShip> ship )
{
	player = ship;
	player->InitSpaceShip(0.0f, -10.0f, 0.0f, 0, 0, 0, 0, 0, 0, -1);
}

std::shared_ptr<PlayerSpaceShip> SpaceShipManager::GetPlayer()
{
	return player;
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
	
	for(unsigned int i = 0; i < projectiles->size(); i++)
	{
		if(*projectiles->at(i)->GetOwner() == *player)
		{
			for(unsigned int x = 0; x < EnemySpaceShips.size(); x++)
			{
				EnemySpaceShips.at(x)->HandleProjectileCollision( projectiles->at(i) );
			}
		}
		else
		{
			player->HandleProjectileCollision( projectiles->at(i) );
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
			player->transformable.setXVel(0.0f);
		}
		//If only left
		if (input->MoveLeft() && !input->MoveRight())
		{
			player->transformable.setXVel(-PLAYER_X_VELOCITY);
		}
		//If only right
		if (!input->MoveLeft() && input->MoveRight())
		{
			player->transformable.setXVel(PLAYER_X_VELOCITY);
		}
	}
	else
	{
		//No movement
		player->transformable.setXVel(0.0f);
	}
}

void SpaceShipManager::HandleYAxisMovement()
{
	if (input->MoveUp()|| input->MoveDown())
	{
		//if up and down
		if (input->MoveUp() && input->MoveDown())
		{
			player->transformable.setYVel(0.0f);
		}
		//If only up
		if (input->MoveUp() && !input->MoveDown())
		{
			player->transformable.setYVel(PLAYER_Y_VELOCITY);
		}
		//If only down
		if (!input->MoveUp() && input->MoveDown())
		{
			player->transformable.setYVel(-PLAYER_Y_VELOCITY);
		}
	}
	else
	{
		//No movement
		player->transformable.setYVel(0.0f);
	}
}

void SpaceShipManager::HandleFrustumCollision()
{
	if( (player->transformable.getXPos() >= FRUSTUM_RIGHT && player->transformable.getXVel() > 0.0f) || 
		(player->transformable.getXPos() <= FRUSTUM_LEFT && player->transformable.getXVel() < 0.0f))
	{
		player->transformable.setXVel(0.0f);
	}
	if( (player->transformable.getYPos() >= FRUSTUM_TOP && player->transformable.getYVel() > 0.0f) || 
		(player->transformable.getYPos() <= FRUSTUM_BOTTOM && player->transformable.getYVel() < 0.0f))
	{
		player->transformable.setYVel(0.0f);
	}
	log << INFO << player->transformable.getYPos() << std::endl;
}

void SpaceShipManager::HandlePlayerRotation()
{
	/*if(input->LeftMouseDownOnce())
	{
		player->InitRotation(Y_AXIS);
	}*/
}

void SpaceShipManager::ResetSpaceships()
{
	EnemySpaceShips.clear();
	EnemyShipsForTransfer.clear();

	if(!player)
	{
		player = std::make_shared<PlayerSpaceShip>();
			
	}
	player->InitSpaceShip(0.0f, -10.0f, 0.0f, 0, 0, 0, 0, 0, 0, -1);

	EnemySpaceShips.push_back(std::make_shared<ImperialStarDestroyer>(player));
	EnemySpaceShips.back()->InitSpaceShip(-200, 200, -600, 200, 0, 1, 0, 0, 0, 1);
}
