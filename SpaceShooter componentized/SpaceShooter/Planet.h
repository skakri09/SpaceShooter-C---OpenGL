/********************************************************************
    created:    25:10:2012   18:17
    filename:   Planet.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Planet_h__
#define Planet_h__

#include "GameObject.h"
#include "VBODrawable.h"
#include "Transformable.h"

class Planet : public GameObject
{
public:
    Planet(/*std::string meshName*/);
    ~Planet();

	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	virtual void CreateGameObject();

	virtual void CreatePlanet(std::string meshName);

	virtual void InitPlanet(float xPos, float yPos, float zPos);


	VBODrawable vboDrawable;
	Transformable transformable;

protected:
	float rotation;
private:
	//std::string meshName;
};

#endif // Planet_h__