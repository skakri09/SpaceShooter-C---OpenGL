/********************************************************************
    created:    10:11:2012   17:23
    filename:   GUIEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef GUIEntry_h__
#define GUIEntry_h__

#include "Transformable.h"
#include "VBODrawable.h"

class GUIEntry
{
public:
	GUIEntry(){}

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(VBODrawable* vbo) = 0;

	Transformable transformable;
};

#endif // GUIEntry_h__