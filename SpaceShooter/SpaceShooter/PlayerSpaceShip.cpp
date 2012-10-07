#include "PlayerSpaceShip.h"

PlayerSpaceShip::PlayerSpaceShip()
	: log("PlayerSpaceship", ERRORX)
{
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

//Experimental VBO/VA arrays
GLfloat spaceshipVertexes[] = {-0.5f, 0.0f, 0.0f,//left bottom
	0.5f, 0.0f, 0.0f,//right bottom
	0.3f, 0.6f, -0.2f,//right top
	-0.3f, 0.6f, -0.2f,//left top
	0.0f, 0.5f, -2.2f//front
};
unsigned int index[] = { 0, 1, 2, //back right triangle
	0, 2, 3, //back left triangle
	0, 3, 4, //left side
	0, 4, 1, //bottom side
	3, 2, 4, //top side
	1, 4, 2 //right side
};

void PlayerSpaceShip::Draw()
{
	glPushMatrix();
	
	glTranslatef(position.getX(), position.getY(), position.getZ());

	glTranslatef(0.f, -10.f, -50.f);
	glScalef(4.0f, 4.0f, 4.0f);
	RotateArroundX(getDeltaTime());
	RotateArroundY(getDeltaTime());
	RotateArroundZ(getDeltaTime());
	//glRotatef(90, 1, 0, 0);
		/// EXPERIMENTING WITH VBO/VA BELOW ///

	/*glVertexPointer(3, GL_FLOAT, 0, spaceshipVertexes);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, index);*/
	
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, spaceshipVertexes);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT,index);
	glDisableClientState(GL_VERTEX_ARRAY);*/
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT,0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	DrawProjectiles(getDeltaTime());
}

void PlayerSpaceShip::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);
	
	CalculatePosition(deltaTime);

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void PlayerSpaceShip::CreateDrawable()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*15, spaceshipVertexes, GL_STATIC_DRAW);

	glGenBuffers(1, &indexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*18, index, GL_STATIC_DRAW);
	
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

void PlayerSpaceShip::InitSpaceship( float startX, float startY, float startZ )
{
	SpaceShip::InitSpaceship(startX, startY, startZ);

	CreateDrawable();
}

