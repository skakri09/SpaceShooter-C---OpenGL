#include "SpaceShipBase.h"

CSpaceShip::CSpaceShip( float xPos /*= 0*/, float yPos /*= 0*/, float zPos /*= 0*/,float direction /*=0*/ )
{
	CDrawable::position.setX(xPos);
	CDrawable::position.setY(yPos);
	CDrawable::position.setZ(zPos);
}

CSpaceShip::~CSpaceShip()
{

}

void CSpaceShip::Draw(GLfloat deltaTime)
{
}

void CSpaceShip::CreateDrawable()
{

}




