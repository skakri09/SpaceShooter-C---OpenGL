#include "CollisionSphere.h"


CollisionSphere::CollisionSphere()
	:log("CollisionSphere", WARN)
{
}

CollisionSphere::~CollisionSphere()
{
}

Vector3D CollisionSphere::IsCollision( BoundingSphere& otherCollidable )
{
	Vector3D ammountOfCollision;
	float distance = LocalMidpoint.Distance(otherCollidable.GetMidpoint());

	if( distance < CollisionRadius + otherCollidable.GetRadius() )
	{
		Vector3D a = otherCollidable.GetMidpoint();

		ammountOfCollision = otherCollidable.GetMidpoint() - CollisionMidpoint;
	}

	return ammountOfCollision;
}

void CollisionSphere::CreateCollisionBox( Mesh& mesh )
{
	AABB::CreateAABB(mesh);
	CalculateDistance();
	log << INFO << "Created a boundingSphere collisionbox" << std::endl;
}

void CollisionSphere::CreateCollisionBox( Lib3dsVector* vertices, unsigned int size )
{
	AABB::CreateAABB(vertices, size);
	CalculateDistance();
	log << INFO << "Created a boundingSphere collisionbox" << std::endl;
}

void CollisionSphere::ApplyTransformations( Transformation& translationInfo )
{
	CollisionMidpoint = LocalMidpoint + translationInfo.position;
	float biggest = translationInfo.scale.getX();
	if(biggest < translationInfo.scale.getY()){biggest = translationInfo.scale.getY();}
	if(biggest < translationInfo.scale.getZ()){biggest = translationInfo.scale.getZ();}

	CollisionRadius = LocalRadius * biggest;
}

Vector3D& CollisionSphere::GetMidpoint()
{
	return CollisionMidpoint;
}

float CollisionSphere::GetRadius()
{
	return CollisionRadius;
}

void CollisionSphere::CalculateDistance()
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

