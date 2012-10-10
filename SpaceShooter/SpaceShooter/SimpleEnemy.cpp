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

	BaseEnemyShip::Draw();

	//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	//glEnableClientState(GL_VERTEX_ARRAY);

	//glVertexPointer(3, GL_FLOAT, 0, 0);
	////meshInfo.numberOfIndices = mesh->indices.size();
	//glDrawElements(GL_TRIANGLES,  18, GL_UNSIGNED_INT,0);

	//glDisableClientState(GL_VERTEX_ARRAY);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	std::shared_ptr<Mesh> mesh = meshLoader.LoadMeshXml("Mesh_PlayerSpaceship.xml");
	meshInfo.numberOfIndices = mesh->indices.size();
	collisionSphere.CreateCollisionBox(*mesh);

	glGenBuffers(1, &meshInfo.vertices);
	glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &meshInfo.normals);
	glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mesh->normals.size(), &mesh->normals[0], GL_STATIC_DRAW);

	/*glGenBuffers(1, &colors);
	glBindBuffer(GL_COLOR_ARRAY, colors);
	glBufferData(GL_COLOR_ARRAY, sizeof(float)*mesh->colors.size(), &mesh->colors[0], GL_STATIC_DRAW);*/

	glGenBuffers(1, &meshInfo.indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &meshInfo.vertices);
	//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*15, enemyVertexes, GL_STATIC_DRAW);

	//glGenBuffers(1, &meshInfo.indices);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*18, enemyIndex, GL_STATIC_DRAW);
}

void SimpleEnemy::Shoot()
{
	SpaceShip::FireGun(FIRE_COOLDOWN_SIMPLE_ENEMY, -SQUARE_BULLET_SPEED_SIMPLE_ENEMY);
}

void SimpleEnemy::InitSpaceship( float startX, float startY, float startZ )
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ);

	CreateDrawable();
}

void SimpleEnemy::HandleAI()
{
		
	float a = position.Distance(*playerShip->getPosition());
	if(a >= 105 && aiStateMachine.GetCurrentState() != "FollowPlayerState")
	/*if(position.getX() <= (playerShip->getXPos()+50)
		&& aiStateMachine.GetCurrentState() != "FollowPlayerState")*/
	{
		aiStateMachine.ChangeState(std::make_shared<FollowPlayerState>());
	}
	//else if(position.getX() >= (playerShip->getXPos()-50)
	//	&& aiStateMachine.GetCurrentState() != "FollowPlayerState")
	//{
	//	aiStateMachine.ChangeState(std::make_shared<FollowPlayerState>());
	//}
	//else if(aiStateMachine.GetCurrentState() != "FireState"
	//	&& ( position.getX() <= (playerShip->getXPos()+50) 
	//	|| position.getX() >= (playerShip->getXPos()-50)))
	else if(aiStateMachine.GetCurrentState() != "FireState"
		&& a < 110)
	{
		aiStateMachine.ChangeState(std::make_shared<FireState>());
	}
}
	