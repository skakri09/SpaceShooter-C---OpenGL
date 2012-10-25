/********************************************************************
    created:    25:10:2012   18:17
    filename:   Planet.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Planet_h__
#define Planet_h__

#include "GameObject.h"


class Planet : public GameObject
{
public:
    Planet(std::string meshName);
    ~Planet();

	virtual void Draw();

	virtual void Update(GLfloat deltaTime);

	virtual void CreateGameObject();

protected:

private:
	std::string meshName;
};

#endif // Planet_h__