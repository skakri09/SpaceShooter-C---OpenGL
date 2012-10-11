#include "PlayerSpaceShip.h"


PlayerSpaceShip::PlayerSpaceShip()
	: log("PlayerSpaceship", ERRORX)
{
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

//Experimental VBO/VA arrays
//GLfloat spaceshipVertexes[] = {-0.5f, 0.0f, 0.0f,//left bottom
//	0.5f, 0.0f, 0.0f,//right bottom
//	0.3f, 0.6f, -0.2f,//right top
//	-0.3f, 0.6f, -0.2f,//left top
//	0.0f, 0.5f, -2.2f//front
//};
//unsigned int index[] = { 0, 1, 2, //back right triangle
//	0, 2, 3, //back left triangle
//	0, 3, 4, //left side
//	0, 4, 1, //bottom side
//	3, 2, 4, //top side
//	1, 4, 2 //right side
//};

void PlayerSpaceShip::Draw()
{
	glPushMatrix();
	
	ApplyTransformations();
	glRotatef(180, 0, 0, 1);//sortof placeholder rotation
	DrawWithArrays();

	//glTranslatef(position.getX(), position.getY(), position.getZ());

	//glTranslatef(0.f, -10.f, -50.f);
	//glScalef(4.0f, 4.0f, 4.0f);

	//Does rotating of spaceship according to its rotation values
	//SpaceShip::Draw();

	//glRotatef(90, 1, 0, 0);
		/// EXPERIMENTING WITH VBO/VA BELOW ///

	/*glVertexPointer(3, GL_FLOAT, 0, spaceshipVertexes);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, index);*/
	
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, spaceshipVertexes);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT,index);
	glDisableClientState(GL_VERTEX_ARRAY);*/
	



	/*
	glEnableClientState(GL_INDEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes);
	
	glVertexPointer(3, GL_FLOAT, 0, NULL);	
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &indexes);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	
	glPopMatrix();
	DrawProjectiles();
}

void PlayerSpaceShip::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);	
	UpdateProjectiles(deltaTime);
	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void PlayerSpaceShip::CreateDrawable()
{
	Mesh3dsLoader loader;
	meshInfo = loader.Load3dsMesh("milfalcon.3ds");
	collisionSphere = *loader.GetBoundingSphere();

	//collisionSphere = loader.GetBoundingSphere();
	//collisionSphere = loader.GetBoundingSphere();
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
	
	/*glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*15, spaceshipVertexes, GL_STATIC_DRAW);

	glGenBuffers(1, &indexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*18, index, GL_STATIC_DRAW);*/

	/*
	CDrawable::displayList = glGenLists(1);
	glNewList(CDrawable::displayList, GL_COMPILE);

	//The normals are commented out, as they are currently not correct, to fix l8r

	//Back quad part of the spaceship
	glBegin(GL_QUADS);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);//bottom left
	glColor3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);//bottom right
	glColor3f(0.9f, 0.0f, 0.0f);
	glVertex3f(0.3f, 0.6f, -0.2f);//top right
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.3f, 0.6f, -0.2f);//top left
	glEnd();

	//Triangle fan of the 4 triangles creating the
	// body of the spaceship
	glBegin(GL_TRIANGLE_FAN);


	//tip point
	glColor3f(0.0f,0.0f,0.0f);                
	glVertex3f(0.0f,  0.5f, -2.2f);

	//bottom left point
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glColor3f(0.0f,0.0f,1.0f);                	
	glVertex3f(-0.5f, 0.0f, 0.0f);

	//top left point
	//glNormal3f(0.0f, -1.0f, 0.0f);
	glColor3f(0.0f,0.0f,0.2f);               
	glVertex3f( -0.3f, 0.6f, -0.2f);

	//top right point
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f,0.0f,1.0f);                	
	glVertex3f( 0.3f, 0.6f, -0.2f);

	//bottom right point
	//glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.2f,0.0f,0.0f);                	
	glVertex3f( 0.5f, 0.0f, 0.0f);

	//bottom left connecting point
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glColor3f(0.0f,0.3f,0.0f);                	
	glVertex3f(-0.5f, 0.0f, 0.0f);

	glEnd();

	glEndList();
	*/
}

void PlayerSpaceShip::Shoot()
{
	SpaceShip::FireGun(FIRE_COOLDOWN_PLAYER, SQUARE_BULLET_SPEED_PLAYER);
}

void PlayerSpaceShip::InitSpaceship( float startX, float startY, float startZ,
	float scaleX, float scaleY, float scaleZ,
	float startRotDeg, float rotX, float rotY, float rotZ)
{
	SpaceShip::InitSpaceship(startX, startY, startZ,
		scaleX, scaleY, scaleZ, 
		startRotDeg, rotX, rotY, rotZ);

	CreateDrawable();
}

