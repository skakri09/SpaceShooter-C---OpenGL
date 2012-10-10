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
#include <lib3ds/types.h>
#include "Transformation.h"
class MeshInfo;
class BoundingSphere : public AABB
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

	//same as above, but takes a reference to an array of floats instead
	virtual void CreateCollisionBox(Lib3dsVector* vertices, unsigned int size);

	void ApplyTransformations(Transformation& translationInfo);

	Vector3D& GetMidpoint();
	
	float GetRadius();

protected:

private:
	Logger log;

	void CalculateDistance();

	Vector3D LocalMidpoint;
	Vector3D LocalFarpoint;
	Vector3D CollisionMidpoint;
	Vector3D CollisionFarpoint;
	float LocalRadius;
	float CollisionRadius;

};

#endif // BoundingSphere_h__
