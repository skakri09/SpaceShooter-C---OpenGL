#include "MenuEntry.h"


MenuEntry::MenuEntry(std::string entryText,
					float xPos, float yPos, float zPos,
					float scale, bool centered)
	:log("MenuEntry", WARN)
{
	Vector3D position(xPos, yPos, zPos);
	EntryTransformable.Init(position, scale, Vector3D::ZeroVec());
	CreateEntryText(&entryText, scale, centered);
	isSelected = false;
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
	if(isSelected)
	{
		glColor3f(0.15f, 0.15f, 0.15f);
	}
	else
	{
		glColor3f(0.05f, 0.05f, 0.05f);
	}
	for(unsigned int i = 0; i < EntryText->vboLetters.size(); i++)
	{
		glPushMatrix();

		EntryText->vboLetters.at(i).stringPosition.ApplyGLTransformations(true, true, false);
		vbo.SetMeshInfo(EntryText->vboLetters.at(i).meshInfo);
		vbo.Draw();
	
		glPopMatrix();
	}
	glColor3f(1.0f, 1.0f, 1.0f);
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
