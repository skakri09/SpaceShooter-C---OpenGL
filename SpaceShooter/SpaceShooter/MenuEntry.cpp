#include "MenuEntry.h"


MenuEntry::MenuEntry(std::string entryText,
					float xPos, float yPos, float zPos,
					float scale )
	:log("MenuEntry", WARN)
{
	CreateEntryText(entryText);
	Vector3D position(xPos, yPos, zPos);
	EntryTransformable.Init(position, scale, Vector3D::ZeroVec());
}

MenuEntry::~MenuEntry()
{
}

void MenuEntry::UpdateEntry(float deltaTime)
{
	EntryTransformable.Update(deltaTime);
	for(unsigned int i = 0; i < EntryText->size(); i++)
	{
		if(EntryText->at(i).meshInfo == NULL)
		{
			//space
		}
		else
		{
			//vbo.SetMeshInfo(EntryText->at(i).meshInfo);
			//vbo.Draw();
		}	
	}
}

void MenuEntry::DrawEntry()
{
	glPushMatrix();
	EntryTransformable.ApplyGLTransformations(true, true, false);

	for(unsigned int i = 0; i < EntryText->size(); i++)
	{
		glPushMatrix();
		if(EntryText->at(i).meshInfo == NULL)
		{
			//space
		}
		else
		{
			EntryText->at(i).stringPosition.ApplyGLTransformations(true, true, false);
			vbo.SetMeshInfo(EntryText->at(i).meshInfo);
			vbo.Draw();
		}	
		glPopMatrix();
	}
	glPopMatrix();
}

void MenuEntry::SetIsSelected( bool isSelected )
{
	this->isSelected = isSelected;
}

void MenuEntry::CreateEntryText( std::string& entryText )
{
	EntryText = TextFactory::Inst()->GetVboString(entryText);
}
