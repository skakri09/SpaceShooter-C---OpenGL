#include "Projectile.h"

CProjectile::CProjectile(float projectileFlytime)
	:log("Projectile", WARN)
{
	PROJECTILE_FLYTIME = projectileFlytime;
	projectileVelocity = -50.0f;
	fired = false;
}

CProjectile::~CProjectile()
{

}

void CProjectile::Draw( GLfloat deltaTime )
{
	if(fired)
	{
		CalculatePosition(deltaTime);
		timeSinceFired += deltaTime;

		// Applying transformations to this matrix to match the position and rotation of the 
		// spaceship when fire was called.
 		glPushMatrix();
		glTranslatef(startPosition.getX(), startPosition.getY(), startPosition.getZ());
		glTranslatef(0.f, -10.f, -50.f);
 		glRotatef(startRotation.getX(), 1.0f, 0.0f, 0.0f);
		glRotatef(startRotation.getY(), 0.0f, 1.0f, 0.0f);
		glRotatef(startRotation.getZ(), 0.0f, 0.0f, 1.0f);
		glScalef(2.f, 2.f, 2.f);
		glTranslatef(0.0f,  0.5f, -2.2f);
		//Draw the projectile in the above object's space which is transformed into the correct
		//position and rotation.
		glPushMatrix();
		glTranslatef(position.getX(), position.getY(), position.getZ());
		glScalef(0.3f, 0.3f, 0.3f);
		glCallList(CDrawable::displayList);
		glPopMatrix();
		glPopMatrix();

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

void CProjectile::FireProjectile( CVector3D startPos, CVector3D startRotation, GLfloat speed )
{
	CDrawable::position = 0.0f;
	CDrawable::velocity = 0.0f;
	timeSinceFired = 0.0f;
	velocity.setZ(projectileVelocity);
	this->startRotation = startRotation;
	this->startPosition = startPos;
	fired = true;
}
