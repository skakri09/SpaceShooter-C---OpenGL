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

void SimpleEnemy::Draw()
{
	glPushMatrix();

	ApplyTransformations();
	//glRotatef(180, 0, 0, 1);//sortof placeholder rotation
	DrawWithArrays();

	glPopMatrix();
	DrawProjectiles();
}

void SimpleEnemy::Update( GLfloat deltaTime )
{
	BaseEnemyShip::Update(deltaTime);
	UpdateProjectiles(deltaTime);
	HandleAI();

	//CalculatePosition(deltaTime);

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void SimpleEnemy::CreateDrawable()
{

	Mesh3dsLoader loader;
	meshInfo = loader.Load3dsMesh("tiebomber.3ds");
	collisionSphere = *loader.GetBoundingSphere();
	//collisionSphere = *meshInfo.collisionSphere;
	//std::shared_ptr<Mesh> mesh = meshLoader.LoadMeshXml("Mesh_PlayerSpaceship.xml");
	//meshInfo.numberOfIndices = mesh->indices.size();
	//collisionSphere.CreateCollisionBox(*mesh);

	//glGenBuffers(1, &meshInfo.vertices);
	//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &meshInfo.normals);
	//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mesh->normals.size(), &mesh->normals[0], GL_STATIC_DRAW);

	///*glGenBuffers(1, &colors);
	//glBindBuffer(GL_COLOR_ARRAY, colors);
	//glBufferData(GL_COLOR_ARRAY, sizeof(float)*mesh->colors.size(), &mesh->colors[0], GL_STATIC_DRAW);*/

	//glGenBuffers(1, &meshInfo.indices);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &meshInfo.vertices);
	//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*15, enemyVertexes, GL_STATIC_DRAW);

	//glGenBuffers(1, &meshInfo.indices);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*18, enemyIndex, GL_STATIC_DRAW);+
}

void SimpleEnemy::Shoot()
{
 	SpaceShip::FireGun(FIRE_COOLDOWN_SIMPLE_ENEMY, -SQUARE_BULLET_SPEED_SIMPLE_ENEMY);
}

void SimpleEnemy::InitSpaceship(float startX, float startY, float startZ,
	float scaleX, float scaleY, float scaleZ,
	float startRotDeg, float rotX, float rotY, float rotZ )
{
	BaseEnemyShip::InitSpaceship(startX, startY, startZ,
		scaleX, scaleY, scaleZ,
		startRotDeg, rotX, rotY, rotZ);

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
	