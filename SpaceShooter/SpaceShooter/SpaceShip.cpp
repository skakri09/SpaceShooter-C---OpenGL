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
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Draw()
{

}

void SpaceShip::Update(GLfloat deltaTime)
{
	this->deltaTime = deltaTime;
	timeSinceLastFired += deltaTime;
}

void SpaceShip::CreateDrawable()
{

}

void SpaceShip::FireGun(float deltaTime, GLfloat fireCooldown, GLfloat projectileSpeed)
{
	timeSinceLastFired += deltaTime;
	if(timeSinceLastFired >= fireCooldown)
	{
		timeSinceLastFired = 0.0f;
		rotation.setX(xAxis.currentAngle);
		rotation.setY(yAxis.currentAngle);
		rotation.setZ(zAxis.currentAngle);

		Projectile* projectile = ProjectileFactory::Inst()->GetProjectile(SIMPLE_BULLET);

		projectile->FireProjectile(position, rotation, projectileSpeed);
		projectiles.push_back(projectile);
	}
}

void SpaceShip::DrawProjectiles( float deltaTime )
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
			(*i)->Draw();
			++i;
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
	glRotatef(xAxis.currentAngle, 1.0f, 0.0f, 0.0f);
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
	glRotatef(zAxis.currentAngle, 0.0f, 0.0f, 1.0f);
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
	glRotatef(yAxis.currentAngle, 0.0f, 1.0f, 0.0f);
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

void SpaceShip::InitSpaceship( float startX, float startY, float startZ )
{
	Drawable::position.setX(startX);
	Drawable::position.setY(startY);
	Drawable::position.setZ(startZ);
}







