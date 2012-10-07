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

 //Set the x, y and z of 3 points that represents 3 corners
 //of a surface. Function will calculate the normal of the
 //surface, and return it as a CVector3d. It is important that
 //the 3 points are given in a clockwise order when looking 
 //down on the surface if we want the normal up towards us.
 Vector3D CalculateNormal( float p1x, float p1y, float p1z,
     float p2x, float p2y, float p2z,
     float p3x, float p3y, float p3z);
 

private:
 
 Vector3D normal;
 Vector3D vector1;
 Vector3D vector2;


};
#endif // NormalCalculator_h__

