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

		glTranslatef(initialStartPosition.getX(), initialStartPosition.getY(), initialStartPosition.getZ());

		//Draw the projectile in the above object's space which is transformed into the correct
		//position and rotation.
		glPushMatrix();

		transformable.ApplyGLTransformations();
		vboDrawable.DrawWithIndices();
		//glTranslatef(position.getX(), position.getY(), position.getZ());
		//glScalef(scale.getX(), scale.getY(), scale.getZ());
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_NORMAL_ARRAY);

		//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		//glVertexPointer(3, GL_FLOAT, 0, 0);

		//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		//glNormalPointer(GL_FLOAT, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
		//glDrawElements(GL_TRIANGLES,  meshInfo.numberOfIndices, GL_UNSIGNED_INT,0);

		//glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_NORMAL_ARRAY);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	Vector3D zeroRotation;
	transformable.Init(*ownerTransformable.getPosition(), zeroRotation, 0, 1,
						ownerTransformable.getDirectionVector());

	transformable.SetScale(scale, scale, scale);
	timeSinceFired = 0.0f;

	Vector3D velocity = transformable.getDirectionVector().Normalize();
	velocity*=projectileVelocity;
	transformable.SetVelocity(velocity);

	initialStartPosition = *transformable.getPosition();
	fired = true;
}

void Projectile::CreateProjectile(ProjectileTypes projectileType,  std::string meshPathFromXmlFolder )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		MeshInfo* _meshInfo = ProjectileFactory::Inst()->GetMeshInfo(projectileType);

		if(_meshInfo == NULL)
		{
			std::string meshPath = "..//xml//Projectiles//";
			meshPath += meshPathFromXmlFolder;
			MeshInfo meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

			vboDrawable.SetMeshInfo(meshInfo);
			collisionSphere = *meshInfo.collisionSphere;
		}
		else
		{
			vboDrawable.SetMeshInfo(*_meshInfo);
			collisionSphere = *_meshInfo->collisionSphere;
		}
	}
}
