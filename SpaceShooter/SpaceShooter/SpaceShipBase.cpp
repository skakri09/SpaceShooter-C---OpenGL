#include "SpaceShipBase.h"

SpaceShip::SpaceShip( float xPos /*= 0*/, float yPos /*= 0*/, float zPos /*= 0*/,float direction /*=0*/ )
{
	Drawable::position.setX(xPos);
	Drawable::position.setY(yPos);
	Drawable::position.setZ(zPos);
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Draw(GLfloat deltaTime)
{
}

void SpaceShip::Update(GLfloat deltaTime)
{

}
void SpaceShip::CreateDrawable()
{

}




