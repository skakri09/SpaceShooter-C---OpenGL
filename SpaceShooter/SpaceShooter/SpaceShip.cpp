#include "SpaceShip.h"

SpaceShip::SpaceShip(int spaceshipHP)
	:log("SpaceShipbase", WARN)
{
	this->SpaceShipMaxHealth = spaceshipHP;
	xAxis.rotating = false;
	yAxis.rotating = false;
	zAxis.rotating = false;
	xAxis.currentAngle = 0.0;
	yAxis.currentAngle = 0.0;
	zAxis.currentAngle = 0.0f;
	deltaTime = 0;
	WasInited = false;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Draw()
{
	ApplyTransformations();
}

void SpaceShip::Update(GLfloat deltaTime)
{
	if(SpaceShipCurrentHealth > 0)
	{
		//CalculatePosition(deltaTime);
		this->deltaTime = deltaTime;
		CalculatePosition(deltaTime);
		UpdateTransformationValues();
		collisionSphere.ApplyTransformations(transformationValues);
		//meshInfo.collisionSphere->ApplyTransformations(transformationValues);
		//collisionSphere.ApplyTransformations(transformationValues)
		//Vector3D dummy;
		//collisionSphere.ApplyTransformations(position, rotation, 0, dummy);
		//RotateArroundX(getDeltaTime());
		//RotateArroundY(getDeltaTime());
		//RotateArroundZ(getDeltaTime());
	}
	else
	{
		KillGameObject();
	}
}

void SpaceShip::CreateGameObject()
{

}

void SpaceShip::FireGun(ProjectileTypes projectileType)
{
	shooterModule.Shoot(projectileType, position, directionVector);
}

void SpaceShip::RotateArroundX(GLfloat deltaTime)
{
	if(xAxis.targetAngle > xAxis.currentAngle)
	{
		xAxis.currentAngle += ROTATE_SPEED*deltaTime;
		if(xAxis.currentAngle > xAxis.targetAngle)
		{
			xAxis.currentAngle = xAxis.targetAngle;
		}
	}
	else
	{
		xAxis.rotating = false;
	}
	
	log << INFO << "Angle around X: " << -xAxis.currentAngle << std::endl;
}

void SpaceShip::RotateArroundZ(GLfloat deltaTime)
{
	if(zAxis.targetAngle > zAxis.currentAngle)
	{
		zAxis.currentAngle += ROTATE_SPEED*deltaTime;
		if(zAxis.currentAngle > zAxis.targetAngle)
		{
			zAxis.currentAngle = zAxis.targetAngle;
		}
	}
	else
	{
		zAxis.rotating = false;
	}
	
	log << INFO << "Angle around Z: " << zAxis.currentAngle << std::endl;
}

void SpaceShip::RotateArroundY( GLfloat deltaTime )
{
	if(yAxis.targetAngle > yAxis.currentAngle)
	{
		yAxis.currentAngle += ROTATE_SPEED*deltaTime;
		if(yAxis.currentAngle > yAxis.targetAngle)
		{
			yAxis.currentAngle = yAxis.targetAngle;
		}
	}
	else
	{
		yAxis.rotating = false;
	}
	
	log << INFO << "Angle around Y: " << yAxis.currentAngle << std::endl;
}

void SpaceShip::InitRotation( Axis axisToRotateArround )
{
	switch(axisToRotateArround)
	{
	case X_AXIS:
		if(!xAxis.rotating)
		{
			xAxis.rotating = true;
			if(xAxis.currentAngle >= 360.0f){ xAxis.currentAngle = 0.0f; }
			xAxis.targetAngle = xAxis.currentAngle + 90.0f;
		}
		break;
	case Y_AXIS:
		if(!yAxis.rotating)
		{
			yAxis.rotating = true;
			if(yAxis.currentAngle >= 360.0f){ yAxis.currentAngle = 0.0f; }
			yAxis.targetAngle = yAxis.currentAngle + 90.0f;
		}
		break;
	case Z_AXIS:
		if(!zAxis.rotating)
		{
			zAxis.rotating = true;
			if(zAxis.currentAngle >= 360.0f){ zAxis.currentAngle = 0.0f; }
			zAxis.targetAngle = zAxis.currentAngle + 90.0f;
		}
		break;
	}
}

void SpaceShip::InitSpaceship( float startX, float startY, float startZ,
	float startRotDeg, float rotX, float rotY, float rotZ,
	float dirVecX, float dirVecY, float dirVecZ)
{
	GameObject::position.setValues(startX, startY, startZ);
	GameObject::directionVector.setValues(dirVecX, dirVecY, dirVecZ);
	GameObject::objectRotation.setValues(rotX, rotY, rotZ);
	GameObject::objectRotationDegrees = startRotDeg;

	isAlive = true;
	SpaceShipCurrentHealth = SpaceShipMaxHealth;
}

void SpaceShip::DrawWithArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnable(GL_COLOR_MATERIAL);
	glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
	glNormalPointer(GL_FLOAT, 0, 0);
	
	/*glBindBuffer(GL_COLOR_ARRAY, colors);
	glColorPointer(3, GL_FLOAT, 0, 0);*/

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	glDrawElements(GL_TRIANGLES, meshInfo.numberOfIndices, GL_UNSIGNED_INT,0);*/
	glDrawArrays(GL_TRIANGLES, 0, meshInfo.numberOfIndices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_COLOR_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SpaceShip::DrawWithIndices()
{
	//glTranslatef(position.getX(), position.getY(), position.getZ());

	////glRotatef(yAxis.currentAngle, 0.0f, 1.0f, 0.0f);
	////glRotatef(xAxis.currentAngle, 1.0f, 0.0f, 0.0f);
	////glRotatef(zAxis.currentAngle, 0.0f, 0.0f, 1.0f);
	//
	//glScalef(scale.getX(), scale.getY(), scale.getZ());
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnable(GL_COLOR_MATERIAL);
	glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
	glNormalPointer(GL_FLOAT, 0, 0);
	
	/*glBindBuffer(GL_COLOR_ARRAY, colors);
	glColorPointer(3, GL_FLOAT, 0, 0);*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	glDrawElements(GL_TRIANGLES, meshInfo.numberOfIndices, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_COLOR_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SpaceShip::HandleProjectileCollision( std::deque<std::shared_ptr<Projectile>>* projectiles )
{
	for(unsigned int i = 0; i < projectiles->size(); i++)
	{
		if(projectiles->at(i)->isFired())
		{
			BoundingSphere projectileColSphere = projectiles->at(i)->GetCollisionSphere();
			Vector3D collAmnt = collisionSphere.IsCollision(projectileColSphere);
			if(collAmnt.getX() > 0 || collAmnt.getY() > 0.0f || collAmnt.getZ() > 0.0f)
			{
				int dmgTaken = projectiles->at(i)->GetProjectileDmg();
				SpaceShipCurrentHealth -= dmgTaken;
				log << WARN << "Spaceship hit! It lost " << dmgTaken << ", " 
					<< SpaceShipCurrentHealth << "/" << SpaceShipMaxHealth <<"HP left" << std::endl;
				projectiles->at(i)->DestroyProjectile();
			}
		}
	}
}
