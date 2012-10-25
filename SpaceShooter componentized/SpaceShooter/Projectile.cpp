#include "Projectile.h"

Projectile::Projectile(	ProjectileTypes projectileType,
						float projectileeVelocity,
						float projectileFlytime, 
						int projectileDmg, 
						float projectileCooldown,
						float scaleX, float scaleY, float scaleZ)
	:log("Projectile", WARN)
{
	this->projectileType = projectileType;
	this->projectileCooldown = projectileCooldown;
	this->PROJECTILE_FLYTIME = projectileFlytime;
	this->projectileDamage = projectileDmg;
	this->projectileVelocity = projectileeVelocity;
	this->fired = false;
	GameObject::scale.setValues(scaleX, scaleY, scaleZ);
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
		glRotatef(objectRotation.getX(), 1.0f, 0.0f, 0.0f);
		glRotatef(objectRotation.getY(), 0.0f, 1.0f, 0.0f);
		glRotatef(objectRotation.getZ(), 0.0f, 0.0f, 1.0f);

		//Draw the projectile in the above object's space which is transformed into the correct
		//position and rotation.
		glPushMatrix();

		glTranslatef(position.getX(), position.getY(), position.getZ());
		glScalef(scale.getX(), scale.getY(), scale.getZ());
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
		glDrawElements(GL_TRIANGLES,  meshInfo.numberOfIndices, GL_UNSIGNED_INT,0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
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
		UpdateTransformationValues();
		timeSinceFired += deltaTime;
		collisionSphere.ApplyTransformations(transformationValues);
		
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

void Projectile::FireProjectile( Vector3D startPos, Vector3D directionVector)
{
	GameObject::position = 0.0f;
	GameObject::velocity = 0.0f;
	GameObject::scale = scale;
	timeSinceFired = 0.0f;
	velocity = directionVector;
	velocity.Normalize();
	velocity *= projectileVelocity;
	this->startPosition = startPos;
	fired = true;
}

void Projectile::UpdateTransformationValues()
{
	GameObject::UpdateTransformationValues();
	transformationValues.position +=startPosition;
}
