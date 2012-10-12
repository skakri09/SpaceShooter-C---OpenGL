#include "PlayerSpaceShip.h"


PlayerSpaceShip::PlayerSpaceShip()
	: log("PlayerSpaceship", ERRORX),
	SpaceShip(50)//the HP
{
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

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
	shooterModule.DrawModule();
}

void PlayerSpaceShip::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);	
	shooterModule.UpdateModule(deltaTime);
	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() 
		<< " Z: " << position.getZ() << std::endl;
}

void PlayerSpaceShip::CreateDrawable()
{
	meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//MilleniumFalcon//MilleniumFalcon.3ds");
	collisionSphere = *meshInfo.collisionSphere;//*loader.GetBoundingSphere();
	WasInited = true;
}

void PlayerSpaceShip::Shoot()
{
	SpaceShip::FireGun();
}

void PlayerSpaceShip::InitSpaceship( float startX, float startY, float startZ,
	float scaleX, float scaleY, float scaleZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	SpaceShip::InitSpaceship(startX, startY, startZ,
		scaleX, scaleY, scaleZ, 
		startRotDeg, rotX, rotY, rotZ,
		dirVecX, dirVecY, dirVecZ);

	if(!WasInited)
	{
		CreateDrawable();
	}
}

