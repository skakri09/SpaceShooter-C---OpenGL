/********************************************************************
	created:	9:10:2012   9:49
	filename: 	BoundingSphere.h
	author:		Kristian Skarseth
	
	purpose:	Bounding sphere collision box
*********************************************************************/
#ifndef BoundingSphere_h__
#define BoundingSphere_h__

#include "Collidable.h"
#include "AABB.h"
#include "Vector3d.h"

class BoundingSphere : public Collidable, public AABB
{
public:
	BoundingSphere();
	virtual ~BoundingSphere();

	//Returns the amount of collision between this and the param
	//vector3D as a vector3d. If there is no collision, the returned 
	//vector3d will be a null-vector
	Vector3D IsCollision(BoundingSphere& otherCollidable);

	//Creates the collisionBox for the spaceship. The default
	//implementation creates a bounding sphere collisionBox
	virtual void CreateCollisionBox(Mesh& mesh);

	void ApplyTransformations(Vector3D& translation,
								Vector3D& rotation,
								float degrees,
								Vector3D& scale);

	Vector3D& GetMidpoint();
	
	float GetRadius();

protected:

private:
	Logger log;

	Vector3D midpoint;
	Vector3D farPoint;
	float radius;

};

#endif // BoundingSphere_h__
