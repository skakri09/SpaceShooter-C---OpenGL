/********************************************************************
created: 11:9:2012   10:50
filename:  NormalCalculator.h
author:  Kristian Skarseth

purpose: Calculates the normal of a surface where given 3 points

*********************************************************************/
#ifndef NormalCalculator_h__
#define NormalCalculator_h__

#include "Vector3d.h"

class NormalCalculator
{
public:

	//The 9 param values should represent 3 points in 3D space.
	//It is important that the 3 points are given in a clockwise 
	//order when looking down on the surface if we want the normal
	//up towards us. p1x, y and z represent 1 point, p2x, y and z
	//the second point and p3x, y and z the third point
	Vector3D CalculateNormal( float p1x, float p1y, float p1z,
		float p2x, float p2y, float p2z,
		float p3x, float p3y, float p3z);

	//Calculates the normal from 3 points (Vector3D) in 3D space. The points must
	//be passed in clockwise order if we want the up vector of the plane.
	Vector3D CalculateNormal(Vector3D* point1, Vector3D* point2, Vector3D* point3);

private:

};
#endif // NormalCalculator_h__

