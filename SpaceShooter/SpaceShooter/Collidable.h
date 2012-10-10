/********************************************************************
    created:    8:10:2012   21:28
    filename:   Collidable.h
    author:     Kristian Skarseth
    
    purpose:    Base object for any type of collisionbox.

*********************************************************************/
#ifndef Collidable_h__
#define Collidable_h__

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>

#include "Mesh.h"
#include "Logger.h"
#include "Vector3d.h"

class Collidable
{
public:
    Collidable();
    ~Collidable();

	////Make return the rectangular overlap
	//virtual bool IsCollision(Collidable& otherCollidable) = 0;

	virtual void ApplyTransformations(Vector3D& translation,
									  Vector3D& rotation,
									  float degrees,
									  Vector3D& scale);

protected:
	//Creates the collisionBox for the spaceship. The default
	//implementation creates a bounding sphere collisionBox
	virtual void CreateCollisionBox(Mesh& mesh) = 0;

private:
	Logger log;
	
};

#endif // Collidable_h__