#include "Transformable.h"


Transformable::Transformable()
{
}

Transformable::~Transformable()
{
}

void Transformable::Init(Vector3D startPos,
							Vector3D rotationAxis,
							float rotationDeg,
							float scale, /* only allowing uniform scaling */ 
							Vector3D directionVector )
{
	SetScale(scale, scale, scale);

	position = startPos;

	this->directionVector = directionVector;

	objectRotationDegrees = rotationDeg;

	this->rotationAxis = rotationAxis;
	UpdateCollisionTransformationInfo();
}

void Transformable::Init( float xPos, float yPos, float zPos, 
						Vector3D rotationAxis, float rotationDeg, 
						float scale, /*only allowing uniform scaling */ 
						Vector3D directionVector )
{
	SetScale(scale, scale, scale);

	Vector3D startPos(xPos, yPos, zPos);

	position = startPos;

	this->directionVector = directionVector;

	objectRotationDegrees = rotationDeg;

	this->rotationAxis = rotationAxis;
	UpdateCollisionTransformationInfo();
}
												/*only allowing uniform scaling */ 
void Transformable::Init( Vector3D startPos, float scale, Vector3D velocity )
{
	SetScale(scale, scale, scale);

	position = startPos;

	directionVector = velocity;//.Normalize();

	objectRotationDegrees = 0.0f;

	rotationAxis = Vector3D::ZeroVec();

	this->velocity = velocity;
	UpdateCollisionTransformationInfo();
}

void Transformable::Update( float deltaTime )
{
	CalculatePosition(deltaTime);
	UpdateCollisionTransformationInfo();
}

void Transformable::ApplyGLTransformations( 
	bool translatef /*= true*/, bool scalef /*= true*/, bool rotatef /*= true*/ )
{
	if(translatef)
	{
		glTranslatef(position.getX(), 
			position.getY(), 
			position.getZ());
	}
	
	if(scalef)
	{
		glScalef(scale.getX(), 
			scale.getY(), 
			scale.getZ());
	}
	
	if(rotatef)
	{
		glRotatef(objectRotationDegrees, 
			rotationAxis.getX(),
			rotationAxis.getY(), 
			rotationAxis.getZ());
	}
}

CollisionTransformationInfo& Transformable::GetCollisionTransformationInfo()
{
	return transformationValues;
}

float Transformable::getXVel()
{
	return velocity.getX();
}
  
float Transformable::getYVel()
{
	return velocity.getY();
}

float Transformable::getZVel()
{
	return velocity.getZ();
}

void Transformable::setXVel(float xVel)
{
	velocity.setX(xVel);
}

void Transformable::setYVel(float yVel)
{
	velocity.setY(yVel);
}

void Transformable::setZVel(float zVel)
{
	velocity.setZ(zVel);
}

float Transformable::getXPos()
{
	return position.getX();
}

float Transformable::getYPos()
{
	return position.getY();
}

float Transformable::getZPos()
{
	return position.getZ();
}

Vector3D* Transformable::getPosition()
{
	return &position;
}

Vector3D* Transformable::getVelocity()
{
	return &velocity;
}

void Transformable::SetVelocity(Vector3D& newVel)
{
	this->velocity = newVel;
}

void Transformable::SetVelocity(float xVel, float yVel, float zVel)
{
	velocity.setX(xVel);
	velocity.setY(yVel);
	velocity.setZ(zVel);
};

void Transformable::SetScale(float x, float y, float z)
{
	scale.setValues(x, y, z);
	transformationValues.scale = scale;
}

Vector3D& Transformable::getDirectionVector()
{
	return directionVector;
}

void Transformable::SetDirectionVector( float xDir, float yDir, float zDir )
{
	directionVector.setValues(xDir, yDir, zDir);
}

void Transformable::SetXPos( float xPos )
{
	position.setX(xPos);
}

void Transformable::SetYPos( float yPos )
{
	position.setY(yPos);
}

void Transformable::SetZPos( float zPos )
{
	position.setZ(zPos);
}



//  P R I V A T E    F U N C T I O N S  //
//**************************************//

void Transformable::CalculatePosition( float deltaTime )
{
	position += (velocity * deltaTime);
}

void Transformable::UpdateCollisionTransformationInfo()
{
	transformationValues.position = position;
	transformationValues.scale = scale;
}

Vector3D& Transformable::GetScale()
{
	return scale;
}

void Transformable::SetPos( Vector3D& newPos )
{
	position = newPos;
}

void Transformable::SetPos( float xPos, float yPos, float zPos )
{
	position.setValues(xPos, yPos, zPos);
}

