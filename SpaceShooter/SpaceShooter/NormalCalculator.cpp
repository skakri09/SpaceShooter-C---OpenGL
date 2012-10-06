#include "NormalCalculator.h"


	Vector3D NormalCalculator::CalculateNormal( float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z )
{
	vector1.setX(p1x - p2x);
	vector1.setY(p1y - p2y);
	vector1.setZ(p1z - p2z);

	vector2.setX(p3x - p2x);
	vector2.setY(p3y - p2y);
	vector2.setZ(p3z - p2z);

	vector1.Normalize();
	vector2.Normalize();

	normal = vector1.CrossProduct(vector2);
	return normal;
}