/********************************************************************
	created:	13:11:2012   11:57
	filename: 	AABBCollisionBox.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef AABBCollisionBox_h__
#define AABBCollisionBox_h__
#include "AABB.h"
#include "CollisionTransformationInfo.h"

#include <gl/glew.h>

class AABBCollisionBox : public AABB
{
public:
	AABBCollisionBox();
	AABBCollisionBox(float minX, float maxX, float minY, float maxY,
						float minZ, float maxZ);
	~AABBCollisionBox();

	//Updates the collisionbx. Should be called every game update, or when we want
	//the collisionsphere to have it's position and scale updated.
	//The parameter collisionTranformationInfo reference should contain updated position
	//and scale of the object this collisionbox is ment for.
	void Update(CollisionTransformationInfo& translationInfo);

	bool IsCollision(AABBCollisionBox* otherCollidable);

	//Creates the collisionBox for the spaceship. from a vector of vertices
	void CreateCollisionBox(std::vector<float>* vertices);

	//same as above, but takes a pointer to a lib3dsvector which contain the vertices instead
	void CreateCollisionBox(Lib3dsVector* vertices, unsigned int size);

	void DrawAABB();

	void CreateSubBox(std::shared_ptr<AABBCollisionBox> newSubBox);

protected:
	Vector3D& GetMidpoint();
	float GetRadius();
	
	bool drawAAB;
	std::vector<std::shared_ptr<AABBCollisionBox>> SubBoxes;
};

#endif // AABBCollisionBox_h__
