/********************************************************************
    created:    11:11:2012   13:24
    filename:   TogglePolygonSmoothEnabledEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef TogglePolygonSmoothEnabledEntry_h__
#define TogglePolygonSmoothEnabledEntry_h__

#include <gl/glew.h>

#include "MenuEntry.h"
class TogglePolygonSmoothEnabledEntry : public MenuEntry
{
public:
    TogglePolygonSmoothEnabledEntry(float xPos, float yPos, float zPos, float scale);
    ~TogglePolygonSmoothEnabledEntry();

	virtual void OnClicked();

	virtual void UpdateEntry(float deltaTime);

	virtual void DrawEntry();
protected:

private:
	std::shared_ptr<VboString> EntryValue;
	Transformable valueTransformable;
	void UpdatePolySmoothValue();
	GLboolean prevPolySmoothVal;
	GLboolean newPolySmoothVal;

};

#endif // TogglePolygonSmoothEnabledEntry_h__