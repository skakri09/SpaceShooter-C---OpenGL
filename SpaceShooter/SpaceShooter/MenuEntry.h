/********************************************************************
    created:    9:11:2012   12:46
    filename:   MenuEntry.h
    author:     Kristian Skarseth
    
    purpose:    Base for Menu Entries
*********************************************************************/
#ifndef MenuEntry_h__
#define MenuEntry_h__

#include "TextFactory.h"

#include "VBODrawable.h"
#include "Transformable.h"
#include "Logger.h"

class MenuEntry
{
public:
    MenuEntry(std::string entryText, 
			float xPos, float yPos, float zPos,
			float scale, bool centered = true );

    ~MenuEntry();

	//Function should do whatever we want to happen when the 
	//menu entry is clicked
	virtual void OnClicked() = 0;

	virtual void UpdateEntry(float deltaTime);

	virtual void DrawEntry();

	void SetIsSelected(bool isSelected);

protected:

private:
	Logger log;

	bool isSelected;

	Transformable EntryTransformable;

	std::shared_ptr<VboString> EntryText;

	void CreateEntryText(std::string* entryText, float scale, bool centered);

	VBODrawable vbo;
};

#endif // MenuEntry_h__