/********************************************************************
*	Created:	2012/09/06  10:09
*	Filename: 	Drawable.h
*	Author:		Kristian Skarseth
*	
*	purpose:	Base class for anything that will be drawn to the screen.
				
	Note:		The class is abstract and cannot be instantiated
*********************************************************************/

#ifndef Drawable_H
#define Drawable_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/gl.h>

#include "Timer.h"
#include "Vector3d.h"



class CDrawable
{
public:

	// Pure virtual function draw, should contain functionality
	// that draws to the screen when overwritten.
	// The function is called from a loop in gameManager that draws
	// all objects added to a CDrawable vector
	virtual void Draw(GLfloat deltaTime) = 0;

	// Pure virtual function CreateDrawable. Once overwritten it should
	// set up and prepare the surface or model we are using once drawing.
	virtual void CreateDrawable() = 0;
	
	void SetVelocity(float xVel, float yVel, float zVel=0)
	{
		velocity.setX(xVel);
		velocity.setY(yVel);
		velocity.setZ(zVel);
	};

	CVector3D getVelocity(){return velocity;}
	float getXVel(){return velocity.getX();}
	float getYVel(){return velocity.getY();}
	float getZVel(){return velocity.getZ();}
	void setXVel(float xVel){velocity.setX(xVel);}
	void setYVel(float yVel){velocity.setY(yVel);}
	void setZVel(float zVel){velocity.setZ(zVel);}

	float getXPos(){return position.getX();}
	float getYPos(){return position.getY();}
	float getZPos(){return position.getZ();}

protected:
	// Calculates the position by adding velocity multiplied by
	// deltaTime (time since last frame) with the current position
	inline void CalculatePosition(GLfloat deltaTime)
	{
		position += (velocity * deltaTime);
	}

	CVector3D position; // Ship Position
	CVector3D velocity; // Ship velocity

	GLuint displayList; // The display list ID

private:

};
#endif // Drawable_H
