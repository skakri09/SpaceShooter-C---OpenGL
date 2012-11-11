/********************************************************************
    created:    11:11:2012   0:45
    filename:   ScoreValueEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ScoreValueEntry_h__
#define ScoreValueEntry_h__

#include "TextEntry.h"
#include "ScoreManager.h"

class ScoreValueEntry : public TextEntry
{
public:
    ScoreValueEntry();
    ~ScoreValueEntry();

	void Init(ManagerInterface* manager);
	void Update(float deltaTime);
	void Draw(VBODrawable* vbo);

private:
	ScoreManager* scoreManager;
	unsigned int displayedScore;

};

#endif // ScoreValueEntry_h__