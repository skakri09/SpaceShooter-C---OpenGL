#include "BaseEnemyShip.h"

#pragma warning(push)
//Disabling warning about using 'this' pointer in ctor. 
#pragma warning(disable: 4355)
BaseEnemyShip::BaseEnemyShip(PlayerSpaceShip* playerShip, 
	std::shared_ptr<AiState> startupState,
	std::shared_ptr<AiState> constantState,
	int enemyHP)
	:log("SimpleEnemyShip", WARN),
	aiStateMachine(this, 
					startupState,
					constantState),
	SpaceShip(enemyHP)
{
	this->playerShip = playerShip;
}
#pragma warning(pop)


BaseEnemyShip::~BaseEnemyShip()
{
}

void BaseEnemyShip::Draw()
{
	//if(IsAlive())
	{
		glPushMatrix();

		transformable.ApplyGLTransformations();
		vboDrawable.DrawWithArrays();

		glPopMatrix();

		shooterModule.DrawModule();
		particleEmitter.DrawParticles();
	}
	
}

void BaseEnemyShip::Update( GLfloat deltaTime )
{
	aiStateMachine.Update(deltaTime);
	SpaceShip::Update(deltaTime);
}

void BaseEnemyShip::Shoot()
{

}


//void BaseEnemyShip::SetAI( EnemyAiType aiType )
//{
//	switch(aiType)
//	{
//	case SIMPLE_AI:
//		shipAI = std::make_shared<SimpleEnemyAI>();
//		break;
//	}
//}
//
