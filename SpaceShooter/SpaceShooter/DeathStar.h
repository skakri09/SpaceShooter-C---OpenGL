/********************************************************************
    created:    14:11:2012   11:14
    filename:   DeathStar.h
    author:     Kristian Skarseth
    
    purpose:    The deathstar. Making it an evironment object as we wont
				interact with it, at least not at this point in time.
*********************************************************************/
#ifndef DeathStar_h__
#define DeathStar_h__

#include "GameObject.h"
#include "VBODrawable.h"
#include "Transformable.h"
#include "MeshFactory.h"
#include "Texturable.h"
class DeathStar : public GameObject
{
public:
    DeathStar();
    ~DeathStar();

	void Draw();

	void Update(GLfloat deltaTime);

	

	VBODrawable vboDrawable;
	Transformable transformable;
	Texturable texturable;
protected:
	//a simple variable used to rotate the planet
	float rotation;

	void InitDeathstar(float xPos, float yPos, float zPos);
	void LoadDeathstar();
private:

};

#endif // DeathStar_h__