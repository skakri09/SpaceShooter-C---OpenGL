#include "AxisAlignedBoundingBox.h"


AxisAlignedBoundingBox::AxisAlignedBoundingBox()
	:log("AxisAlignedBounxingBox", WARN)
{
}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
{
}


bool AxisAlignedBoundingBox::IsCollision( Collidable& otherCollidable )
{
	//if (RectA.X1 < RectB.X2 && RectA.X2 > RectB.X1 &&
	//	RectA.Y1 < RectB.Y2 && RectA.Y2 > RectB.Y1) 

	//	if not (B.x > A.x+A.dx or B.x+B.dx < A.x or
	//		B.y > A.y+A.dy or B.y+B.dy < A.y or
	//		B.z > A.z+A.dz or B.z+B.dz < A.z)
	return false;
}

void AxisAlignedBoundingBox::CreateCollisionBox(Mesh& mesh)
{
	AABB::CreateAABB(mesh);
}

void AxisAlignedBoundingBox::ApplyTransformations(Vector3D& translation,
													Vector3D& rotation,
													float degrees,
													Vector3D& scale)
{
	Collidable::ApplyTransformations(translation, rotation, degrees, scale);
}
