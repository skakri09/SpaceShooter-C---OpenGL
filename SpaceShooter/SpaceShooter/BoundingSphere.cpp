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
	float distance = LocalMidpoint.Distance(otherCollidable.GetMidpoint());

	if( distance < CollisionRadius + otherCollidable.GetRadius() )
	{
		Vector3D a = otherCollidable.GetMidpoint();

		ammountOfCollision = otherCollidable.GetMidpoint() - CollisionMidpoint;
	}

	return ammountOfCollision;
}

void BoundingSphere::CreateCollisionBox(Mesh& mesh)
{
	AABB::CreateAABB(mesh);

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

	log << INFO << "Created a boundingSphere collisionbox" << std::endl;
}

void BoundingSphere::ApplyTransformations(Vector3D& translation,
											Vector3D& rotation,
											float degrees,
											Vector3D& scale)
{
	CollisionMidpoint = LocalMidpoint + translation;
	Vector3D middleMan = LocalRadius;
	middleMan *= scale;
	CollisionFarpoint = middleMan;
	CollisionRadius = CollisionMidpoint.Distance(CollisionFarpoint);
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
