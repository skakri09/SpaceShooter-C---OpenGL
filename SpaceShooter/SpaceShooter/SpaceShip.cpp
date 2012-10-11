#include "SpaceShip.h"

SpaceShip::SpaceShip()
	:log("SpaceShipbase", WARN)
{
	xAxis.rotating = false;
	yAxis.rotating = false;
	zAxis.rotating = false;
	xAxis.currentAngle = 0.0;
	yAxis.currentAngle = 0.0;
	zAxis.currentAngle = 0.0f;
	timeSinceLastFired = 0.0f;
	deltaTime = 0;
	timeSinceLastFired = 0;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Draw()
{
	ApplyTransformations();
	//DrawWithIndices();
}

void SpaceShip::Update(GLfloat deltaTime)
{
	//CalculatePosition(deltaTime);
	this->deltaTime = deltaTime;
	timeSinceLastFired += deltaTime;
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

void SpaceShip::CreateDrawable()
{

}

void SpaceShip::FireGun(GLfloat fireCooldown, GLfloat projectileSpeed)
{
	//timeSinceLastFired += this->getDeltaTime();
	if(timeSinceLastFired >= fireCooldown)
	{
		timeSinceLastFired = 0.0f;
		rotation.setX(xAxis.currentAngle);
		rotation.setY(yAxis.currentAngle);
		rotation.setZ(zAxis.currentAngle);

		Projectile* projectile = ProjectileFactory::Inst()->GetProjectile(SIMPLE_BULLET);
		Vector3D scale;scale.setValues(0.3f, 0.3f, 0.3f);
		projectile->FireProjectile(position, rotation, scale, projectileSpeed);
		projectiles.push_back(projectile);
	}
}

void SpaceShip::DrawProjectiles( )
{
	for(auto i = projectiles.begin(); i != projectiles.end(); i++)
	{
		if( (*i)->isFired() )
		{
			(*i)->Draw();
		}
	}
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
	float scaleX, float scaleY, float scaleZ,
	float startRotDeg, float rotX, float rotY, float rotZ)
{
	Drawable::position.setX(startX);
	Drawable::position.setY(startY);
	Drawable::position.setZ(startZ);
	
	Drawable::SetScale(scaleX, scaleY, scaleZ);
	Drawable::startRotation.setValues(rotX, rotY, rotZ);
	Drawable::startRotationDegrees = startRotDeg;

	//collisionSphere = 
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
	//glEnableClientState(GL_COLOR_ARRAY);
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
	//glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_COLOR_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool SpaceShip::WasHitByPorjectile( std::vector<Projectile*>* projectiles )
{
	for(unsigned int i = 0; i < projectiles->size(); i++)
	{
		if(projectiles->at(i)->isFired())
		{
			BoundingSphere asd = projectiles->at(i)->GetCollisionSphere();
			Vector3D dsa = collisionSphere.IsCollision(asd);
			if(dsa.getX() > 0 || dsa.getY() > 0.0f || dsa.getZ() > 0.0f)
			{
				return true;
			}
		}
	}
	return false;
}

void SpaceShip::UpdateProjectiles( float deltaTime )
{
	for(auto i = projectiles.begin(); i != projectiles.end();)
	{
		if( !(*i)->isFired() )
		{
			i = projectiles.erase(i);
		}
		else
		{
			(*i)->Update(deltaTime);
			++i;
		}
	}
}
