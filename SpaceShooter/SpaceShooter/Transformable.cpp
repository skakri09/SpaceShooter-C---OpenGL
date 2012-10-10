#include "Transformable.h"


Transformable::Transformable()
{
}

Transformable::~Transformable()
{

}


void Transformable::ApplyTransformations()
{
	glRotatef(degrees, rotation.getX(), rotation.getY(), rotation.getZ());
}


void Transformable::UpdateTransformations( float deltaTime )
{
	CalculatePosition(deltaTime);


}

void Transformable::CalculatePosition( float deltaTime )
{
	position += (velocity * deltaTime);
}

void Transformable::SetVelocity( float xVel, float yVel, float zVel )
{
	velocity.setValues(xVel, yVel, zVel);
}

void Transformable::SetRotation( float degrees, float x, float y, float z )
{
	this->degrees = degrees; 
	rotation.setValues(x, y, z);
}

