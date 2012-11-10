/********************************************************************
    created:    10:11:2012   17:40
    filename:   HPEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef HPEntry_h__
#define HPEntry_h__

#include "TextEntry.h"
#include "SpaceShipManager.h"

class HPEntry : public TextEntry
{
public:
    HPEntry();
    ~HPEntry();

	void Init();
	void Update(float deltaTime);
	void Draw(VBODrawable* vbo);
private:
	int currentlyDisplayedHP;
};

#endif // HPEntry_h__