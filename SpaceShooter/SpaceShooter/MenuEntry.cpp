#include "MenuEntry.h"


MenuEntry::MenuEntry(std::string entryText,
					float xPos, float yPos, float zPos,
					float scale )
	:log("MenuEntry", WARN)
{
	CreateEntryText(entryText);
}

MenuEntry::~MenuEntry()
{
}

void MenuEntry::UpdateEntry()
{

}

void MenuEntry::DrawEntry()
{
	for(unsigned int i = 0; i < EntryText->size(); i++)
	{
		vbo.SetMeshInfo(EntryText->at(i).meshInfo)
	}
}

void MenuEntry::SetIsSelected( bool isSelected )
{
	this->isSelected = isSelected;
}

void MenuEntry::CreateEntryText( std::string& entryText )
{
	EntryText = TextFactory::Inst()->GetVboString(entryText);
}
