#include "Collidable.h"


Collidable::Collidable() :log("Collidable", WARN)
{
}

Collidable::~Collidable()
{
}

void Collidable::ApplyTransformations( Vector3D& translation, Vector3D& rotation, float degrees, Vector3D& scale )
{
	glTranslatef(translation.getX(), translation.getY(), translation.getZ());

	glRotatef(degrees, rotation.getX(), rotation.getY(), rotation.getZ());

	glScalef(scale.getX(), scale.getY(), scale.getZ());
}
