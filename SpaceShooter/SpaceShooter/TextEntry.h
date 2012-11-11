/********************************************************************
    created:    10:11:2012   17:15
    filename:   TextEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef TextEntry_h__
#define TextEntry_h__

#include "GUIEntry.h"
#include "TextFactory.h"

class TextEntry : public GUIEntry
{
public:
    TextEntry();
	
	//Initialize the text entry. Should set position, scale, rotation,
	//text and all other information relevant
	virtual void Init(){}
	virtual void Init(ManagerInterface* manager){}

	virtual void Update(float deltaTime);
	virtual void Draw(VBODrawable* vbo);

protected:
	std::shared_ptr<VboString> VBOString;
	std::string updatedString;
	std::string stringInUse;

private:
	
};

#endif // TextEntry_h__