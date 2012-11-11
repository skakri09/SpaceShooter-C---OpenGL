/********************************************************************
    created:    10:11:2012   23:28
    filename:   ScoreTextEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ScoreTextEntry_h__
#define ScoreTextEntry_h__

#include "TextEntry.h"
#include "ScoreManager.h"

class ScoreTextEntry : public TextEntry
{
public:
    ScoreTextEntry();
    ~ScoreTextEntry();

	void Init();
	void Update(float deltaTime);
	void Draw(VBODrawable* vbo);

};

#endif // ScoreTextEntry_h__