/********************************************************************
    created:    14:11:2012   21:26
    filename:   ImageEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ImageEntry_h__
#define ImageEntry_h__

#include "GUIEntry.h"
#include "Texturable.h"
#include "VBODrawable.h"
#include "MeshFactory.h"
#include "SpaceShipManager.h"
#include "ProjectileTypes.h"

class ImageEntry : public GUIEntry
{
public:
    ImageEntry(std::string textureName, float xPos, float yPos, float zPos, float scale);
	~ImageEntry();

	virtual void Init(ManagerInterface* manager){}
	virtual void Init();

	virtual void Update(float deltaTime){}
	virtual void Draw(VBODrawable* vbo);


protected:
	Texturable texture;
	VBODrawable _vbo;

	std::string textureName;
	std::string texturePath;
};

#endif // ImageEntry_h__