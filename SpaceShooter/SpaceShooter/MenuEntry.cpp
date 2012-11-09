#include "MenuEntry.h"


MenuEntry::MenuEntry(std::string entryText,
					float xPos, float yPos, float zPos,
					float scale, bool centered)
	:log("MenuEntry", WARN)
{
	Vector3D position(xPos, yPos, zPos);
	EntryTransformable.Init(position, scale, Vector3D::ZeroVec());
	CreateEntryText(&entryText, scale, centered);
}

MenuEntry::~MenuEntry()
{
}

void MenuEntry::UpdateEntry(float deltaTime)
{
	EntryTransformable.Update(deltaTime);
}

void MenuEntry::DrawEntry()
{
	glPushMatrix();
	EntryTransformable.ApplyGLTransformations(true, true, false);

	for(unsigned int i = 0; i < EntryText->vboLetters.size(); i++)
	{
		glPushMatrix();

		EntryText->vboLetters.at(i).stringPosition.ApplyGLTransformations(true, true, false);
		vbo.SetMeshInfo(EntryText->vboLetters.at(i).meshInfo);
		vbo.Draw();
	
		glPopMatrix();
	}
	glPopMatrix();
}

void MenuEntry::SetIsSelected( bool isSelected )
{
	this->isSelected = isSelected;
}

void MenuEntry::CreateEntryText( std::string* entryText, float scale, bool centered )
{
	EntryText = TextFactory::Inst()->GetVboString(entryText);
	if(centered)
	{
		EntryText->stringLength*= scale;
		EntryTransformable.SetXPos(EntryTransformable.getXPos() - (EntryText->stringLength/2) );
	}
}
