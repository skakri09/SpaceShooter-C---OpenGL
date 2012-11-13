/********************************************************************
	created:	13:11:2012   11:57
	filename: 	AABBCollisionBox.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef AABBCollisionBox_h__
#define AABBCollisionBox_h__

#include "Logger.h"
#include "AABB.h"
#include "CollisionTransformationInfo.h"
class AABBCollisionBox : public AABB
{
public:
	AABBCollisionBox();
	~AABBCollisionBox();

	//Updates the collisionbx. Should be called every game update, or when we want
	//the collisionsphere to have it's position and scale updated.
	//The parameter collisionTranformationInfo reference should contain updated position
	//and scale of the object this collisionbox is ment for.
	void Update(CollisionTransformationInfo& translationInfo);

	Vector3D IsCollision(AABBCollisionBox* otherCollidable);

	//Creates the collisionBox for the spaceship. from a vector of vertices
	void CreateCollisionBox(std::vector<float>* vertices);

	//same as above, but takes a pointer to a lib3dsvector which contain the vertices instead
	void CreateCollisionBox(Lib3dsVector* vertices, unsigned int size);



protected:
	Vector3D& GetMidpoint();

	float GetRadius();

private:
	Logger log;
};

#endif // AABBCollisionBox_h__
