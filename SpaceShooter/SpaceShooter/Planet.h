/********************************************************************
    created:    25:10:2012   18:17
    filename:   Planet.h
    author:     Kristian Skarseth
    
    purpose:    A gameobject representing a simple planet
*********************************************************************/
#ifndef Planet_h__
#define Planet_h__

#include "GameObject.h"
#include "VBODrawable.h"
#include "Transformable.h"
#include "MeshFactory.h"

class Planet : public GameObject
{
public:
    Planet();
    ~Planet();

	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	//Loads and prepares a the param planet
	virtual void CreatePlanet(std::string meshName);

	VBODrawable vboDrawable;
	Transformable transformable;

protected:
	//a simple variable used to rotate the planet
	float rotation;

	virtual void InitPlanet(float xPos, float yPos, float zPos);

private:
	
};

#endif // Planet_h__