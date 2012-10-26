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
							float scale, /*Cheating and only allowing uniform scaling */ 
							Vector3D directionVector )
{
	SetScale(scale, scale, scale);

	position = startPos;

	this->directionVector = directionVector;
}

void Transformable::Update( float deltaTime )
{
	CalculatePosition(deltaTime);
	UpdateCollisionTransformationInfo();
}

void Transformable::ApplyGLTransformations()
{
	glTranslatef(position.getX(), 
		position.getY(), 
		position.getZ());
	
	glScalef(scale.getX(), 
		scale.getY(), 
		scale.getZ());
	
	glRotatef(objectRotationDegrees, 
		objectRotation.getX(),
		objectRotation.getY(), 
		objectRotation.getZ());
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

void Transformable::setVelocity(Vector3D& newVel)
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


