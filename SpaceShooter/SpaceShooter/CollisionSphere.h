/********************************************************************
    created:    10:10:2012   22:31
    filename:   CollisionSphere.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef CollisionSphere_h__
#define CollisionSphere_h__

#include "AABB.h"
#include "Vector3d.h"
#include "Transformation.h"
#include "Mesh.h"

class CollisionSphere : public AABB
{
public:
    CollisionSphere();
    ~CollisionSphere();

	//Returns the amount of collision between this and the param
	//vector3D as a vector3d. If there is no collision, the returned 
	//vector3d will be a null-vector
	Vector3D IsCollision(BoundingSphere& otherCollidable);

	//Creates the collisionBox for the spaceship. The default
	//implementation creates a bounding sphere collisionBox
	void CreateCollisionBox(Mesh& mesh);

	//same as above, but takes a reference to an array of floats instead
	void CreateCollisionBox(Lib3dsVector* vertices, unsigned int size);

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

#endif // CollisionSphere_h__