#include "PlayerSpaceShip.h"

CPlayerSpaceShip::CPlayerSpaceShip(float startX, float startY, float startZ, float direction)
	: log("PlayerSpaceship", ERRORX),
	  CSpaceShip(startX, startY, startZ, direction)
{
	xAxis.rotating = false;
	yAxis.rotating = false;
	zAxis.rotating = false;
	xAxis.currentAngle = 0.0;
	yAxis.currentAngle = 0.0;
	zAxis.currentAngle = 0.0f;
	timeSinceLastFired = 0.0f;
}

CPlayerSpaceShip::~CPlayerSpaceShip()
{
}

void CPlayerSpaceShip::Draw( GLfloat deltaTime )
{
	timeSinceLastFired += deltaTime;
	CalculatePosition(deltaTime);

	glPushMatrix();

	glTranslatef(position.getX(), position.getY(), position.getZ());
	glTranslatef(0.f, -10.f, -50.f);
	
	RotateArroundX(deltaTime);
	RotateArroundY(deltaTime);
	RotateArroundZ(deltaTime);
	
	glScalef(4.f, 4.f, 4.f);

	glCallList(CDrawable::displayList);
	glPopMatrix();

	DrawProjectiles(deltaTime);

	log << INFO << "X: " << position.getX()<< " Y: " << position.getY() << " Z: " << position.getZ() << std::endl;
}

void CPlayerSpaceShip::CreateDrawable()
{
	CDrawable::displayList = glGenLists(1);
	glNewList(CDrawable::displayList, GL_COMPILE);

	/*The normals are commented out, as they are currently not correct, to fix l8r*/

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
}

void CPlayerSpaceShip::RotateArroundX(GLfloat deltaTime)
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
	glRotatef(xAxis.currentAngle, 1.0f, 0.0f, 0.0f);
	log << INFO << "Angle around X: " << -xAxis.currentAngle << std::endl;
}

void CPlayerSpaceShip::RotateArroundZ(GLfloat deltaTime)
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
	glRotatef(zAxis.currentAngle, 0.0f, 0.0f, 1.0f);
	log << INFO << "Angle around Z: " << zAxis.currentAngle << std::endl;
}


void CPlayerSpaceShip::RotateArroundY( GLfloat deltaTime )
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
	glRotatef(yAxis.currentAngle, 0.0f, 1.0f, 0.0f);
	log << INFO << "Angle around Y: " << yAxis.currentAngle << std::endl;
}

void CPlayerSpaceShip::InitRotation( Axis axisToRotateArround )
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

void CPlayerSpaceShip::FireGun(float deltaTime)
{
	timeSinceLastFired += deltaTime;
	if(timeSinceLastFired >= FIRE_COOLDOWN)
	{
		timeSinceLastFired = 0.0f;
		rotation.setX(xAxis.currentAngle);
		rotation.setY(yAxis.currentAngle);
		rotation.setZ(zAxis.currentAngle);

		CProjectile* projectile = CProjectileFactory::Inst()->GetProjectile(SIMPLE_BULLET);

		projectile->FireProjectile(position, rotation, 1.0f);
		projectiles.push_back(projectile);
	}
}

void CPlayerSpaceShip::DrawProjectiles( float deltaTime )
{
	for(auto i = projectiles.begin(); i != projectiles.end();)
	{
		if( !(*i)->isFired() )
		{
			i = projectiles.erase(i);
		}
		else
		{
			(*i)->Draw(deltaTime);
			++i;
		}
	}
}





