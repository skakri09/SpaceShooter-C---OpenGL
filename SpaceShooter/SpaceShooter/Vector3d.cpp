#include "Vector3D.h"

CVector3D::CVector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
CVector3D::~CVector3D()
{
}

float CVector3D::Distance(const CVector3D& vector1, CVector3D& vector2)
{
	return sqrt( pow((vector2.x - vector1.x), 2) + 
		pow((vector2.x - vector1.y), 2) );
}

CVector3D& CVector3D::operator= (const CVector3D& vector2)
{
	if(this == &vector2)
		return *this;

	x = vector2.x;
	y = vector2.y;
	z = vector2.z;
	return *this;
}

CVector3D& CVector3D::operator=( const float value )
{
	x = value;
	y = value;
	z = value;
	return *this;
}

CVector3D& CVector3D::operator+=(const CVector3D& vector2)
{
	x += vector2.x;
	y += vector2.y;
	z += vector2.z;
	return *this;
}

CVector3D& CVector3D::operator-=(const CVector3D& vector2)
{
	x -= vector2.x;
	y -= vector2.y;
	z -= vector2.z;
	return *this;
}

CVector3D& CVector3D::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

CVector3D& CVector3D::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

const CVector3D CVector3D::operator+(const CVector3D& vector2) const
{
	return (CVector3D(*this) += vector2);
}

const CVector3D CVector3D::operator-(const CVector3D& vector2) const
{
	return (CVector3D(*this) -= vector2);
}

const CVector3D CVector3D::operator*(const float scalar) const
{
	return (CVector3D(*this) *= scalar);
}

const CVector3D CVector3D::operator/(const float scalar) const
{
	return (CVector3D(*this) /= scalar);
}

bool CVector3D::operator==(const CVector3D& vector2) const
{
	return ((x == vector2.x) && (y == vector2.y));
}

bool CVector3D::operator!=(const CVector3D& vector2) const
{
	return !((x == vector2.x) && (y == vector2.y));
}

void CVector3D::Invert()
{
	x > 0 ? x=(0-x) : x = abs(x);
	y > 0 ? y=(0-x) : y = abs(x);
	z > 0 ? z=(0-x) : z = abs(x);
}

void CVector3D::InvertX()
{
	x > 0 ? x=(0-x) : x = abs(x);
}

void CVector3D::InvertY()
{
	y > 0 ? y=(0-x) : y = abs(x);
}

void CVector3D::InvertZ()
{
	z > 0 ? z=(0-x) : z = abs(x);
}

float CVector3D::Magnitude() const
{
	return sqrt( (x*x) + (y*y) + (z*z) );
}

float CVector3D::Normalize()
{
	float mag = Magnitude();
	x/=mag;
	y/=mag;
	z/=mag;
	return mag;
}

float CVector3D::DotProduct( const CVector3D& vector2 ) const
{
	CVector3D retVal = *this;
	retVal.x *= vector2.x;
	retVal.y *= vector2.y;
	retVal.z *= vector2.z;
	
	return retVal.x + retVal.y + retVal.z;
}

CVector3D CVector3D::CrossProduct( const CVector3D& vector2 ) const
{
	CVector3D crossProduct;
	crossProduct.x = this->y*vector2.z - this->z*vector2.y;
	crossProduct.y = this->z*vector2.x - this->x*vector2.z;
	crossProduct.z = this->x*vector2.y - this->y*vector2.x;

	return crossProduct;
}


