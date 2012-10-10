#include "BoundingSphere.h"


BoundingSphere::BoundingSphere()
	:log("BoundingSphere", WARN)
{
}

BoundingSphere::~BoundingSphere()
{
}

Vector3D BoundingSphere::IsCollision( BoundingSphere& otherCollidable )
{
	Vector3D ammountOfCollision = 0;
	float distance = midpoint.Distance(otherCollidable.GetMidpoint());

	if( distance < radius + otherCollidable.GetRadius() )
	{
		ammountOfCollision = otherCollidable.GetMidpoint() - midpoint;
	}

	return ammountOfCollision;
}

void BoundingSphere::CreateCollisionBox(Mesh& mesh)
{
	AABB::CreateAABB(mesh);

	midpoint.setValues(m_Right - m_Width/2, m_Top - m_Height/2, m_Front - m_Depth/2);
	radius = 0;
	farPoint = 0;
	float distance;

	distance = farPoint.Distance(AABB::m_LeftTopBack);
	if(distance > radius) { radius = distance; }
	
	distance = farPoint.Distance(AABB::m_RightTopBack);
	if(distance > radius) { radius = distance; }
	
	distance = farPoint.Distance(AABB::m_LeftTopFront);
	if(distance > radius) { radius = distance; }
	
	distance = farPoint.Distance(AABB::m_RightTopFront);
	if(distance > radius) { radius = distance; }
	
	distance = farPoint.Distance(AABB::m_LeftBottomBack);
	if(distance > radius) { radius = distance; }
	
	distance = farPoint.Distance(AABB::m_RightBottomBack);
	if(distance > radius) { radius = distance; }
	
	distance = farPoint.Distance(AABB::m_LeftBottomFront);
	if(distance > radius) { radius = distance; }
	
	distance = farPoint.Distance(AABB::m_RightBottomFront);
	if(distance > radius) { radius = distance; }

	log << INFO << "Created a boundingSphere collisionbox" << std::endl;
}

void BoundingSphere::ApplyTransformations(Vector3D& translation,
											Vector3D& rotation,
											float degrees,
											Vector3D& scale)
{
	Collidable::ApplyTransformations(translation, rotation, degrees, scale);
}

Vector3D& BoundingSphere::GetMidpoint()
{
	return midpoint;
}

float BoundingSphere::GetRadius()
{
	return radius;
}
