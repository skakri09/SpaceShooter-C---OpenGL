/********************************************************************
	created:	2012/04/15
	created:	15:4:2012   23:02
	filename: 	Vector3D.h

	author:		Kristian Skarseth
	
	purpose:	Simple vector 3d class. Can be used for anything from
				a position in 3d, to acceleration, force, velocity and so on.

*********************************************************************/
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

#include "Logger.h"
#include "Timer.h"

double inline __declspec (naked) __fastcall sqrt14(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
} 

class Vector3D
{
public:

	Vector3D(float x = 0, float y = 0, float z = 0);
	~Vector3D();
	
	static Vector3D ZeroVec();

	void setValues(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}

	inline void setX(float x)	{this->x = x;}
	inline void setY(float y)	{this->y = y;}
	inline void setZ(float z)	{this->z = z;}

	inline float getX()			{return x;}
	inline float getY()			{return y;}
	inline float getZ()			{return z;}
	
	//Inverts the values.
	void Invert();
	void InvertX();
	void InvertY();
	void InvertZ();
	
	// Rotates the vector with an angle, not implemented
	void Rotate(Vector3D v, Vector3D axis, const float angle);

	// Returns the magnitude of this vector
	float Magnitude() const;

	// Normalizes this vector
	float Normalize(); 

	// Returns the dot product of this vector and param vector
	float DotProduct(const Vector3D& vector2) const;

	// Returns the cross product of this vector and the param vector (crossing this with param)
	Vector3D CrossProduct(const Vector3D& vector2) const;

	// Get the distance between two vectors
	static float Distance(const Vector3D& vector1, Vector3D& vector2);

	// Get the distance between two vectors
	float Distance(Vector3D& vector2);

	// Get the distance between the two vectors in the xy plane only
	float XYDistance(Vector3D& vector2);

	// Give left Vector3D the values of right Vector3D
	Vector3D& operator= (const Vector3D& vector2);

	// Give this Vector3D the values of the float
	Vector3D& operator= (const float value);

	// Add the values of right Vector3D to the right Vector3D
	Vector3D& operator+=(const Vector3D& vector2);

	// Subtract the values of right Vector3D from left Vector3D
	Vector3D& operator-=(const Vector3D& vector2);

	// Multiply the Vector3D with a scalar value
	Vector3D& operator*=(const float scalar);

	// Multiply the Vector3D with a Vector3D
	Vector3D& operator*=(const Vector3D& vector2);

	// Divide the Vector3D with a scalar value
	Vector3D& operator/=(const float scalar);

	// Adds left and right Vector3D and returns the value
	const Vector3D operator+(const Vector3D& vector2) const;

	// Subtracts right Vector3D from left Vector3D and returns the value
	const Vector3D operator-(const Vector3D& vector2) const;

	// Multiplies Vector3D with the scalar and returns the value
	const Vector3D operator*(const float scalar) const;

	// Multiplies Vector3D with the vector3d and returns the value
	const Vector3D operator*(const Vector3D& vector2) const;

	// Divides Vector3D with the scalar and returns the value
	const Vector3D operator/(const float scalar) const;

	// Returns true if left Vector3D equals the right Vector3D. False otherwise
	bool operator==(const Vector3D& vector2) const;

	// Returns rue if left Vector3D is not equal to the right Vector3D. False otherwise.
	bool operator!=(const Vector3D& vector2) const;


private:
	float x;
	float y;
	float z;

	
};

#endif

