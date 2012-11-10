/********************************************************************
    created:    10:11:2012   21:05
    filename:   LivesEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef LivesEntry_h__
#define LivesEntry_h__

#include "TextEntry.h"
#include "SpaceShipManager.h"

class LivesEntry : public TextEntry
{
public:
    LivesEntry();
    ~LivesEntry();

	void Init();
	void Update(float deltaTime);
	void Draw(VBODrawable* vbo);

private:
	int currentlyDisplayedLives;
};

#endif // LivesEntry_h__