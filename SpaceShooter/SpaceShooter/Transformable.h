/********************************************************************
    created:    10:10:2012   12:06
    filename:   Transformable.h
    author:     Kristian Skarseth
    
    purpose:    Provides a class with the functionality to move, scale
				and rotate(not done yet). 
*********************************************************************/
#ifndef Transformable_h__
#define Transformable_h__

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/glew.h>

#include "CollisionTransformationInfo.h"


class Transformable
{
public:
    Transformable();

    ~Transformable();

	void Init(Vector3D startPos,
		float scale,	//Cheating and only allowing uniform scaling
		Vector3D velocity);

	void Init(Vector3D startPos,
		Vector3D rotation,
		float scale,	//Cheating and only allowing uniform scaling
		Vector3D directionVector);

	void Init(float xPos, float yPos, float zPos,
		Vector3D rotation,
		float scale,	//Cheating and only allowing uniform scaling
		Vector3D directionVector);

	
	//Updates everything in this component. Should be called once every game
	//update, or whenever the component owner requires this component to update
	void Update(float deltaTime);

	//Does the glTranslatef, glScalef and glRotatef function calls
	//with the variables we have stored in this class.
	void ApplyGLTransformations(bool translatef = true, 
		bool scalef = true, bool rotatef = true);

	//Various get and set functions for velocity and position.
	//Creating several ways of setting and getting the variables
	//as the most convenient of doing it varies trough the game
	float getXVel();
	float getYVel();
	float getZVel();
	
	void setXVel(float xVel);
	void setYVel(float yVel);
	void setZVel(float zVel);

	float getXPos();
	float getYPos();
	float getZPos();

	Vector3D* getPosition();
	Vector3D* getVelocity();
	void SetVelocity(Vector3D& newVel);

	void SetVelocity(float xVel, float yVel, float zVel);

	void SetPos(Vector3D& newPos);
	void SetPos(float xPos, float yPos, float zPos);
	void SetXPos(float xPos);
	void SetYPos(float yPos);
	void SetZPos(float zPos);
	//Sets the scale of this object. Also updates the scale
	//in the transformationValues struct
	void SetScale(float x, float y, float z);

	Vector3D& GetScale();
	CollisionTransformationInfo& GetCollisionTransformationInfo();
	
	Vector3D& getDirectionVector();
	void SetDirectionVector(float xDir, float yDir, float zDir);
	
private:
	// Calculates the position by adding velocity multiplied by
	// deltaTime (time since last frame) with the current position
	void CalculatePosition(float deltaTime);

	void UpdateCollisionTransformationInfo();

	//Struct object containing transformation information
	//on this object. Will be updated on update() calls 
	//and can be passed to objects requiring knowledge
	//of this objects displacement/rotation etc
	CollisionTransformationInfo transformationValues;

	//A normalized directional vector. The vector should
	//always be updated to the direction of the gameObject
	Vector3D directionVector;

	Vector3D position;	// The translated position
	Vector3D velocity;	// The velocity of the object

	Vector3D scale;		// The scale of the object this class is representing

	//The rotation of the gameObject
	Vector3D rotation;

	float objectRotationDegrees;
};

#endif // Transformable_h__