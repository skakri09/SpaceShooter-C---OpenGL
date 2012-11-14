/********************************************************************
    created:    14:11:2012   22:10
    filename:   ProjectileIcon.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ProjectileIcon_h__
#define ProjectileIcon_h__

#include "ImageEntry.h"
#include "SpaceShipManager.h"
#include "ProjectileTypes.h"

enum IconState{UNKNOWN, INACTIVE, ACTIVE};

class ProjectileIcon : public ImageEntry
{
public:
    ProjectileIcon(ProjectileTypes projectileType, 
					std::string textureName, 
					float xPos, float yPos, float zPos, float scale);
    ~ProjectileIcon();

	void Init();

	void Update(float deltaTime);

	void Draw(VBODrawable* vbo);

protected:

private:
	ProjectileTypes thisType;
	
	IconState iconState;
};

#endif // ProjectileIcon_h__