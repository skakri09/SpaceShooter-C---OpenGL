/********************************************************************
    created:    10:10:2012   12:06
    filename:   Transformable.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Transformable_h__
#define Transformable_h__

#include <windows.h>
#endif
#include <gl/gl.h>

#include "Transformation.h"


class Transformable
{
public:
    Transformable();
    ~Transformable();

	void ApplyTransformations();

	void UpdateTransformations(float deltaTime);

	void SetVelocity(float xVel, float yVel, float zVel);
	void SetRotation(float degrees, float x, float y, float z);

protected:

private:
	void CalculatePosition(float deltaTime);

	Vector3D position;	// The translated position
	Vector3D velocity;	// The velocity of the object

	Vector3D scale;		// The translated scale

	Vector3D rotation;	// The axis to rotate arround
	float degrees;		// The degrees to rotate
};

#endif // Transformable_h__