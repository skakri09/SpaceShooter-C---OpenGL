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


#include "MeshInfo.h"
#include "Timer.h"
#include "Vector3d.h"
#include "Transformation.h"
#include "BoundingSphere.h"
#include "MeshFactory.h"

class GameObject
{
public:
	GameObject(){isAlive = true;}
	~GameObject(){}

	// Pure virtual function draw, should contain functionality
	// that draws to the screen when overwritten.
	virtual void Draw() = 0;

	// Pure virtual function Update, should contain everything
	// needed to update the particular object.
	virtual void Update(GLfloat deltaTime) = 0;

	// Pure virtual function CreateDrawable. The overwritten version
	// should load and prepare everything the gameObject requires to
	// do perform it's functionality. Generally this will be loading
	// the mesh file associated with the object.
	virtual void CreateGameObject() = 0;

	
	//Various get and set functions for velocity and position.
	//Creating several ways of setting and getting the variables
	//as the most convenient of doing it way varies trought the game
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

	//Sets the scale of this object. Also updates the scale
	//in the transformationValues struct
	void SetScale(float x, float y, float z)
	{
		scale.setValues(x, y, z);
		transformationValues.scale = scale;
	}
	
	//Returns a reference to this objects collisionSphere object
	BoundingSphere& GetCollisionSphere(){return collisionSphere;}

	//Sets the object to not being alive, meaning the object
	//wont get rendered or updated 
	virtual void KillGameObject(){isAlive = false;}
	
	//Returns wheither or not this object is alive. The object should
	//not be rendered or updated if it's not alive
	bool GameObjectAlive(){return isAlive;}
protected:

	// Calculates the position by adding velocity multiplied by
	// deltaTime (time since last frame) with the current position
	inline void CalculatePosition(GLfloat deltaTime)
	{
		position += (velocity * deltaTime);
	}

	//Updates a struct with transformation values for this object
	//so that we can pass the struct to the collisionBox object
	//assigned to this object and let it update itself.
	virtual void UpdateTransformationValues()
	{
		transformationValues.position = position;
		transformationValues.scale = scale;
	}
	
	//Applies the transformations for this object using the
	//the vector3ds position, scale and rotation
	virtual void ApplyTransformations()
	{
		glTranslatef(position.getX(), position.getY(), position.getZ());
		glScalef(scale.getX(), scale.getY(), scale.getZ());
		glRotatef(objectRotationDegrees, objectRotation.getX(), objectRotation.getY(), objectRotation.getZ());
	}

	//Struct object containing transformation information
	//on this object. Will be updated on update() calls 
	//and can be passed to objects requiring knowledge
	//of this objects displacement/rotation etc
	Transformation transformationValues;

	//BoundingSphere object acting as this objects collision box.
	BoundingSphere collisionSphere;

	Vector3D position;	// Ship Position
	Vector3D velocity;	// Ship velocity
	Vector3D scale;		// Ship scale
 	
	//A normalized directional vector. The vector
	//should always be updated to the direction of 
	//the gameObject
	Vector3D directionVector;

	//The rotation of the gameObject
	Vector3D objectRotation;
	float objectRotationDegrees;
	
	//This game objects mesh info object. The MeshInfo
	//object contains VBO IDs for drawing
	MeshInfo meshInfo;

	bool isAlive;
private:

};
#endif // Drawable_H
