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
#include <gl/glew.h>
#include <gl/gl.h>


#include "Mesh.h"
#include "Timer.h"
#include "Vector3d.h"
#include "Transformation.h"
#include "BoundingSphere.h"

class Drawable
{
public:

	// Pure virtual function draw, should contain functionality
	// that draws to the screen when overwritten.
	virtual void Draw() = 0;

	// Pure virtual function Update, should contain everything
	// needed to update the particular object.
	virtual void Update(GLfloat deltaTime) = 0;

	// Pure virtual function CreateDrawable. Once overwritten it should
	// set up and prepare the surface or model we are using once drawing.
	virtual void CreateDrawable() = 0;

	
	//Various get and set functions for velocity and position.
	//Creating several ways of setting and getting the variables
	//as the most convenient of doing it way varies a lot.
	float getXVel(){return velocity.getX();}
	float getYVel(){return velocity.getY();}
	float getZVel(){return velocity.getZ();}
	void setXVel(float xVel){velocity.setX(xVel);}
	void setYVel(float yVel){velocity.setY(yVel);}
	void setZVel(float zVel){velocity.setZ(zVel);}

	float getXPos(){return position.getX();}
	float getYPos(){return position.getY();}
	float getZPos(){return position.getZ();}
	
	Vector3D* getPosition(){return &position;}
	Vector3D* getVelocity(){return &velocity;}
	void setVelocity(Vector3D& newVel){this->velocity = newVel;}

	void SetVelocity(float xVel, float yVel, float zVel)
	{
		velocity.setX(xVel);
		velocity.setY(yVel);
		velocity.setZ(zVel);
	};
	
	void SetScale(float x, float y, float z)
	{
		scale.setValues(x, y, z);
		transformationValues.scale = scale;
	}
	
	std::shared_ptr<BoundingSphere> GetCollisionSphere(){return collisionSphere;}

protected:

	// Calculates the position by adding velocity multiplied by
	// deltaTime (time since last frame) with the current position
	inline void CalculatePosition(GLfloat deltaTime)
	{
		position += (velocity * deltaTime);
		transformationValues.position = position;
		transformationValues.scale = scale;
	}
	
	//Applies the transformations for this object using the
	//the vector3ds position, scale and rotation
	virtual void ApplyTransformations()
	{
		glTranslatef(position.getX(), position.getY(), position.getZ());
		glScalef(scale.getX(), scale.getY(), scale.getZ());
		glRotatef(startRotationDegrees, startRotation.getX(), startRotation.getY(), startRotation.getZ());
	}

	Transformation transformationValues;
	std::shared_ptr<BoundingSphere> collisionSphere;

	Vector3D position; // Ship Position
	Vector3D velocity; // Ship velocity
	Vector3D scale;
	Vector3D startRotation;
	float startRotationDegrees;

	MeshInfo meshInfo;
	GLuint indices;
	GLuint normals;
	GLuint vertices;
	GLuint colors;

private:

};
#endif // Drawable_H
