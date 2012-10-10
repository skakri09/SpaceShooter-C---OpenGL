/********************************************************************
	created:	9:10:2012   10:42
	filename: 	AxisAlignedBoundingBox.h
	author:		Kristian Skarseth
	
	purpose:	Axis aligned bounding collision box

	note:		Using m_ prefix for member variables for once. This is not
				my usual style, but since I'm going soft and creating public
				functions with the same names as the member variables I decided
				to give them the "member" prefix.
*********************************************************************/
#ifndef AxisAlignedBoundingBox_h__
#define AxisAlignedBoundingBox_h__

#include "Collidable.h"
#include "AABB.h"
class AxisAlignedBoundingBox : public Collidable, public AABB
{
public:
	AxisAlignedBoundingBox();
	~AxisAlignedBoundingBox();

	bool IsCollision(Collidable& otherCollidable);

	float Height();
	float Width();
	float Depth();

	float Left();
	float Right();
	float Top();
	float Bottom();
	float Back();
	float Front();

	void ApplyTransformations(Vector3D& translation,
								Vector3D& rotation,
								float degrees,
								Vector3D& scale);

	//Creates the collisionBox for the spaceship. The default
	//implementation creates a bounding sphere collisionBox
	void CreateCollisionBox(Mesh& mesh);

protected:
	

private:
	Logger log;

	

};

#endif // AxisAlignedBoundingBox_h__
