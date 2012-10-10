#include "Projectile.h"

Projectile::Projectile(float projectileFlytime)
	:log("Projectile", WARN)
{
	PROJECTILE_FLYTIME = projectileFlytime;
	projectileVelocity = -100.0f;
	fired = false;
}

Projectile::~Projectile()
{

}

void Projectile::Draw()
{
	if(fired)
	{

		// Applying transformations to this matrix to match the position and rotation of the 
		// spaceship when fire was called.
		glPushMatrix();

		glTranslatef(startPosition.getX(), startPosition.getY(), startPosition.getZ());
		//glTranslatef(0.f, -10.f, -50.f);
		glRotatef(startRotation.getX(), 1.0f, 0.0f, 0.0f);
		glRotatef(startRotation.getY(), 0.0f, 1.0f, 0.0f);
		glRotatef(startRotation.getZ(), 0.0f, 0.0f, 1.0f);
		//glScalef(2.f, 2.f, 2.f);
		//glTranslatef(0.0f,  0.5f, -2.2f);

		//Draw the projectile in the above object's space which is transformed into the correct
		//position and rotation.
		glPushMatrix();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT,0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glTranslatef(position.getX(), position.getY(), position.getZ());
		glScalef(0.3f, 0.3f, 0.3f);
		//glCallList(Drawable::displayList);
		
		glPopMatrix();
		glPopMatrix();
		log << INFO << position.getZ() << std::endl;
	}
}

void Projectile::Update(GLfloat deltaTime)
{
	if(fired)
	{
		CalculatePosition(deltaTime);
		timeSinceFired += deltaTime;

		//Makes sure we stop drawing the projectile if it's been "airborne" longer then or 
		//equal to the constant PROJECTILE_FLYTIME
		if(timeSinceFired >= PROJECTILE_FLYTIME)
		{
			fired = false;
			timeSinceFired = 0.0f;
		}

		log << INFO << "X: " << position.getX() 
			<< " Y: " << position.getY() 
			<< " Z: " << position.getZ() << std::endl;
	}
}

void Projectile::FireProjectile( Vector3D startPos, Vector3D startRotation, GLfloat speed )
{
	Drawable::position = 0.0f;
	Drawable::velocity = 0.0f;
	timeSinceFired = 0.0f;
	velocity.setZ(-speed);//setting to negative z so we don't have to do that other places
	this->startRotation = startRotation;
	this->startPosition = startPos;
	fired = true;
}
