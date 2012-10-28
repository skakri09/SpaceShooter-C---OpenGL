#include "Projectile.h"

Projectile::Projectile(	ProjectileTypes projectileType,
	float projectileeVelocity,
	float projectileFlytime, 
	int projectileDmg, 
	float projectileCooldown,
	float scale)
	:log("Projectile", WARN)
{
	this->projectileType = projectileType;
	this->projectileCooldown = projectileCooldown;
	this->PROJECTILE_FLYTIME = projectileFlytime;
	this->projectileDamage = projectileDmg;
	this->projectileVelocity = projectileeVelocity;
	this->fired = false;
	this->scale = scale;
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

		//glTranslatef(initialStartPosition.getX(), initialStartPosition.getY(), initialStartPosition.getZ());

		//Draw the projectile in the above object's space which is transformed into the correct
		//position and rotation.
		glPushMatrix();

		transformable.ApplyGLTransformations(true, true, false);
		vboDrawable.DrawWithIndices();


		glPopMatrix();
		glPopMatrix();
	}
}

void Projectile::Update(GLfloat deltaTime)
{
	if(fired)
	{
		transformable.Update(deltaTime);
		timeSinceFired += deltaTime;
		collisionSphere.Update(transformable.GetCollisionTransformationInfo());
		
		//Makes sure we stop drawing the projectile if it's been "airborne" longer then or 
		//equal to the constant PROJECTILE_FLYTIME
		if(timeSinceFired >= PROJECTILE_FLYTIME)
		{
			fired = false;
			timeSinceFired = 0.0f;
		}
	}
}

void Projectile::FireProjectile( Transformable& ownerTransformable)
{
	Vector3D zeroVec;
	transformable.Init(*ownerTransformable.getPosition(), zeroVec, 0, 1,
						ownerTransformable.getDirectionVector());

	transformable.SetScale(scale, scale, scale);
	timeSinceFired = 0.0f;

	Vector3D velocity = transformable.getDirectionVector();//.Normalize();
	velocity.Normalize();
	velocity*=projectileVelocity;
	transformable.SetVelocity(velocity);

	initialStartPosition = *ownerTransformable.getPosition();
	fired = true;
}

