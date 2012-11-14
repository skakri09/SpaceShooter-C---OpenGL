#include "ProjectileIcon.h"


ProjectileIcon::ProjectileIcon( ProjectileTypes projectileType, 
	std::string textureName, 
	float xPos, float yPos, float zPos, float scale )
	:ImageEntry(textureName, xPos, yPos, zPos, scale)
{
	thisType = projectileType;
	iconState = UNKNOWN;
}

ProjectileIcon::~ProjectileIcon()
{
}

void ProjectileIcon::Init()
{
	ImageEntry::Init();
	if(SpaceShipManager::Inst()->GetPlayer()->GetActiveProjectileType() == thisType)
	{
		iconState = ACTIVE;
	}
	else
	{
		if(SpaceShipManager::Inst()->GetPlayer()->ProjectileTypeKnown(thisType))
		{
			iconState = INACTIVE;
		}
		else
		{
			iconState = UNKNOWN;
		}
	}
}

void ProjectileIcon::Update( float deltaTime )
{
	if(SpaceShipManager::Inst()->GetPlayer()->GetActiveProjectileType() == thisType)
	{
		iconState = ACTIVE;
	}
	else
	{
		if(SpaceShipManager::Inst()->GetPlayer()->ProjectileTypeKnown(thisType))
		{
			iconState = INACTIVE;
		}
		else
		{
			iconState = UNKNOWN;
		}
	}
}

void ProjectileIcon::Draw( VBODrawable* vbo )
{
	if(iconState == INACTIVE)
	{
		glColor4f(1, 1, 1, 0.3f);
	}
	else if(iconState == UNKNOWN)
	{
		glColor4f(1, 1, 1, 0.05f);
	}
	ImageEntry::Draw(vbo);
	glColor4f(1, 1, 1, 1);
}

