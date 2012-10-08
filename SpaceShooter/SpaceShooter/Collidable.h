/********************************************************************
    created:    8:10:2012   21:28
    filename:   Collidable.h
    author:     Kristian Skarseth
    
    purpose:    An object that handles everything that has to do with
				collision for any object. It has functions to check 
				collision against this or other object, as well as for
				creating collision boxes.
	note:		Using m_ prefix for member variables for once. This is not
				my usual style, but since I'm going soft and creating public
				functions with the same names as the member variables I decided
				to give them the "member" prefix.
*********************************************************************/
#ifndef Collidable_h__
#define Collidable_h__

#include "Mesh.h"
#include "Logger.h"
#include "Vector3d.h"

class Collidable
{
public:
    Collidable();
    ~Collidable();

	//Make return the rectangular overlap
	bool CheckForCollision(Collidable& otherCollidable);

	float Height();
	float Width();
	float Depth();

	float Left();
	float Right();
	float Top();
	float Bottom();
	float Back();
	float Front();
protected:

private:
	Logger log;
	
	float m_Height;
	float m_Width;
	float m_Depth;

	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
	float m_Back;
	float m_Front;

	//Creates the collisionBox for the spaceship. The default
	//implementation creates a bounding sphere collisionBox
	void CreateCollisionBox(Mesh& mesh);
};

#endif // Collidable_h__