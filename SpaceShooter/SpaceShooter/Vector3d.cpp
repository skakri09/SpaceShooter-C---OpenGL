#include "Vector3D.h"

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3D::~Vector3D()
{
}

float Vector3D::Distance(const Vector3D& vector1, Vector3D& vector2)
{
	return sqrt( pow((vector2.x - vector1.x), 2) + 
		pow((vector2.x - vector1.y), 2) );
}

float Vector3D::Distance( Vector3D& vector2 )
{
	return sqrt( pow((vector2.x - x), 2) + 
		pow((vector2.x - y), 2) );
}

Vector3D& Vector3D::operator= (const Vector3D& vector2)
{
	if(this == &vector2)
		return *this;

	x = vector2.x;
	y = vector2.y;
	z = vector2.z;
	return *this;
}

Vector3D& Vector3D::operator=( const float value )
{
	x = value;
	y = value;
	z = value;
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& vector2)
{
	x += vector2.x;
	y += vector2.y;
	z += vector2.z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vector2)
{
	x -= vector2.x;
	y -= vector2.y;
	z -= vector2.z;
	return *this;
}

Vector3D& Vector3D::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3D& Vector3D::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

const Vector3D Vector3D::operator+(const Vector3D& vector2) const
{
	return (Vector3D(*this) += vector2);
}

const Vector3D Vector3D::operator-(const Vector3D& vector2) const
{
	return (Vector3D(*this) -= vector2);
}

const Vector3D Vector3D::operator*(const float scalar) const
{
	return (Vector3D(*this) *= scalar);
}

const Vector3D Vector3D::operator/(const float scalar) const
{
	return (Vector3D(*this) /= scalar);
}

bool Vector3D::operator==(const Vector3D& vector2) const
{
	return ((x == vector2.x) && (y == vector2.y));
}

bool Vector3D::operator!=(const Vector3D& vector2) const
{
	return !((x == vector2.x) && (y == vector2.y));
}

void Vector3D::Invert()
{
	x > 0 ? x=(0-x) : x = abs(x);
	y > 0 ? y=(0-x) : y = abs(x);
	z > 0 ? z=(0-x) : z = abs(x);
}

void Vector3D::InvertX()
{
	x > 0 ? x=(0-x) : x = abs(x);
}

void Vector3D::InvertY()
{
	y > 0 ? y=(0-x) : y = abs(x);
}

void Vector3D::InvertZ()
{
	z > 0 ? z=(0-x) : z = abs(x);
}

float Vector3D::Magnitude() const
{
	return sqrt( (x*x) + (y*y) + (z*z) );
}

float Vector3D::Normalize()
{
	float mag = Magnitude();
	x/=mag;
	y/=mag;
	z/=mag;
	return mag;
}

float Vector3D::DotProduct( const Vector3D& vector2 ) const
{
	Vector3D retVal = *this;
	retVal.x *= vector2.x;
	retVal.y *= vector2.y;
	retVal.z *= vector2.z;
	
	return retVal.x + retVal.y + retVal.z;
}

Vector3D Vector3D::CrossProduct( const Vector3D& vector2 ) const
{
	Vector3D crossProduct;
	crossProduct.x = this->y*vector2.z - this->z*vector2.y;
	crossProduct.y = this->z*vector2.x - this->x*vector2.z;
	crossProduct.z = this->x*vector2.y - this->y*vector2.x;

	return crossProduct;
}


