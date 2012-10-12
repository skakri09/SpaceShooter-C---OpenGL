/********************************************************************
	created:	9:10:2012   9:49
	filename: 	BoundingSphere.h
	author:		Kristian Skarseth
	
	purpose:	Bounding sphere collision box
*********************************************************************/
#ifndef BoundingSphere_h__
#define BoundingSphere_h__

#include <vector>
#include <memory>
#include <lib3ds/types.h>
#include "AABB.h"
#include "Vector3d.h"
#include "Transformation.h"
//#include "MeshInfo.h"

class BoundingSphere : public AABB
{
public:
	BoundingSphere();
	~BoundingSphere();

	//Returns the amount of collision between this and the param
	//vector3D as a vector3d. If there is no collision, the returned 
	//vector3d will be a null-vector
	Vector3D IsCollision(BoundingSphere& otherCollidable);

	//Creates the collisionBox for the spaceship. from a vector of vertices
	void CreateCollisionBox(std::vector<float>* vertices);

	//same as above, but takes a pointer to an array of floats instead
	void CreateCollisionBox(Lib3dsVector* vertices, unsigned int size);

	void ApplyTransformations(Transformation& translationInfo);

	Vector3D& GetMidpoint();
	
	float GetRadius();

protected:

private:
	void CalculateDistance();

	Vector3D LocalMidpoint;
	Vector3D LocalFarpoint;
	Vector3D CollisionMidpoint;
	Vector3D CollisionFarpoint;
	float LocalRadius;
	float CollisionRadius;

};

#endif // BoundingSphere_h__
