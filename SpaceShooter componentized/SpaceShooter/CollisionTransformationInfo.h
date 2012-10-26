/********************************************************************
    created:    10:10:2012   11:56
    filename:   Transformation.h
    author:     Kristian Skarseth
    
    purpose:    A class holding tranformation attributes. 
*********************************************************************/
#ifndef Transformation_h__
#define Transformation_h__

#include "Vector3d.h"

class CollisionTransformationInfo
{
public:

	Vector3D position;	// The translated position
	Vector3D scale;		// The translated scale
};

#endif // Transformation_h__