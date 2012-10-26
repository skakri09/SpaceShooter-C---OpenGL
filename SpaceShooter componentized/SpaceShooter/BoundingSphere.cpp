#include "BoundingSphere.h"
#include <lib3ds/types.h>

BoundingSphere::BoundingSphere()
{
}

BoundingSphere::~BoundingSphere()
{
}

Vector3D BoundingSphere::IsCollision( BoundingSphere& otherCollidable)
{
	Vector3D ammountOfCollision = 0;
	float distance = CollisionMidpoint.Distance(otherCollidable.GetMidpoint());

	if( distance < CollisionRadius + otherCollidable.GetRadius() )
	{
        Vector3D a = otherCollidable.GetMidpoint();

		ammountOfCollision = otherCollidable.GetMidpoint() - CollisionMidpoint;
	}

	return ammountOfCollision;
}

void BoundingSphere::CreateCollisionBox( std::vector<float>* vertices )
{
	AABB::CreateAABB(vertices);
	CalculateDistance();
}

void BoundingSphere::CreateCollisionBox(Lib3dsVector* vertices, unsigned int size)
{
	AABB::CreateAABB(vertices, size);
	CalculateDistance();
}


void BoundingSphere::Update(CollisionTransformationInfo& translationInfo)
{
	float biggest = translationInfo.scale.getX();
	if(biggest < translationInfo.scale.getY()){biggest = translationInfo.scale.getY();}
	if(biggest < translationInfo.scale.getZ()){biggest = translationInfo.scale.getZ();}

	CollisionMidpoint = (LocalMidpoint*biggest) + translationInfo.position;
	

	CollisionRadius = LocalRadius * biggest;
	//Vector3D middleMan = LocalRadius;
	//middleMan *= translationInfo.scale;
	//CollisionFarpoint = middleMan + translationInfo.position;
	//CollisionRadius = CollisionMidpoint.Distance(CollisionFarpoint);
	//Collidable::ApplyTransformations(translation, rotation, degrees, scale);
	/*glTranslatef(translation.getX(), translation.getY(), translation.getZ());

	glScalef(scale.getX(), scale.getY(), scale.getZ());*/
}

Vector3D& BoundingSphere::GetMidpoint()
{
	return CollisionMidpoint;
}

float BoundingSphere::GetRadius()
{
	return CollisionRadius;
}

void BoundingSphere::CalculateDistance()
{
	LocalMidpoint.setValues(m_Right - m_Width/2, m_Top - m_Height/2, m_Front - m_Depth/2);
	LocalRadius = 0;
	LocalFarpoint = 0;
	float distance;

	distance = LocalFarpoint.Distance(AABB::m_LeftTopBack);
	if(distance > LocalRadius) { LocalRadius = distance; }

	distance = LocalFarpoint.Distance(AABB::m_RightTopBack);
	if(distance > LocalRadius) { LocalRadius = distance; }

	distance = LocalFarpoint.Distance(AABB::m_LeftTopFront);
	if(distance > LocalRadius) { LocalRadius = distance; }

	distance = LocalFarpoint.Distance(AABB::m_RightTopFront);
	if(distance > LocalRadius) { LocalRadius = distance; }

	distance = LocalFarpoint.Distance(AABB::m_LeftBottomBack);
	if(distance > LocalRadius) { LocalRadius = distance; }

	distance = LocalFarpoint.Distance(AABB::m_RightBottomBack);
	if(distance > LocalRadius) { LocalRadius = distance; }

	distance = LocalFarpoint.Distance(AABB::m_LeftBottomFront);
	if(distance > LocalRadius) { LocalRadius = distance; }

	distance = LocalFarpoint.Distance(AABB::m_RightBottomFront);
	if(distance > LocalRadius) { LocalRadius = distance; }
}
