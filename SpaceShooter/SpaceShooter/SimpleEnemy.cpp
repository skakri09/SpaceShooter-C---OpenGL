#include "SimpleEnemy.h"

SimpleEnemy::SimpleEnemy(PlayerSpaceShip* playerShip)
	: log("SimpleEnemy", WARN),
	 BaseEnemyShip(playerShip, std::make_shared<IdleState>(),
					std::make_shared<EnemySpaceshipConstantState>())
	
{

}

SimpleEnemy::~SimpleEnemy()
{
}

//Experimental VBO/VA arrays
GLfloat enemyVertexes[] = {-0.5f, 0.0f, 0.0f,//left bottom
	0.5f, 0.0f, 0.0f,//right bottom
	0.3f, 0.6f, -0.2f,//right top
	-0.3f, 0.6f, -0.2f,//left top
	0.0f, 0.5f, -2.2f//front
};

unsigned int enemyIndex[] = { 0, 1, 2, //back right triangle
	0, 2, 3, //back left triangle
	0, 3, 4, //left side
	0, 4, 1, //bottom side
	3, 2, 4, //top side
	1, 4, 2 //right side
};


void SimpleEnemy::Draw()
{
	glPushMatrix();

	glTranslatef(position.getX(), position.getY(), position.getZ());

	glTranslatef(0.f, -10.f, -50.f);
	glScalef(4.0f, 4.0f, 4.0f);
	glRotatef(180, 0, 1, 0);//turned against the player

	RotateArroundX(getDeltaTime());
	RotateArroundY(getDeltaTime());
	RotateArroundZ(getDeltaTime());


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT,0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPopMatrix();
	DrawProjectiles(getDeltaTime());
}

void SimpleEnemy::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);

	HandleAI();

	CalculatePosition(deltaTime);

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void SimpleEnemy::CreateDrawable()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*15, enemyVertexes, GL_STATIC_DRAW);

	glGenBuffers(1, &indexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*18, enemyIndex, GL_STATIC_DRAW);
}

void SimpleEnemy::Shoot()
{
	SpaceShip::FireGun(FIRE_COOLDOWN_SIMPLE_ENEMY, -SQUARE_BULLET_SPEED_SIMPLE_ENEMY);
}

void SimpleEnemy::InitSpaceship( float startX, float startY, float startZ )
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ);

	CreateDrawable();

	//SetAI(SIMPLE_AI);
}

void SimpleEnemy::HandleAI()
{
	float a = position.Distance(*playerShip->getPosition());
	if(position.Distance(*playerShip->getPosition()) > 200 
		&& aiStateMachine.GetCurrentState() != "FollowPlayerState")
	{
		aiStateMachine.ChangeState(std::make_shared<FollowPlayerState>());
	}
}
	