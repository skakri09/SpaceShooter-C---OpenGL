/********************************************************************
*	Created:	2012/09/06  10:04
*	Filename: 	SpaceShip.h
*	Author:		Kristian Skarseth
*	
*	purpose:	Base class for any spaceship, enemy or player.
				Contains functionality to draw and set/get position and
				velocity of the spaceship.

				Position and velocity comes in form of a CVector3D, and the
				Draw() function is inherited from the Drawable abstract class 
				which works as an interface in this case.
*********************************************************************/

#ifndef SpaceShip_H
#define SpaceShip_H

#include "Drawable.h"

enum Direction {CLOCKWISE, ANTI_CLOCKWISE};
class CSpaceShip : public CDrawable
{
public:
	CSpaceShip(float xPos = 0, float yPos = 0, float zPos = 0, float direction =0);

	~CSpaceShip();

	virtual void Draw(GLfloat deltaTime);
	virtual void CreateDrawable();


protected:
	

private:

};

#endif // SpaceShip_H
