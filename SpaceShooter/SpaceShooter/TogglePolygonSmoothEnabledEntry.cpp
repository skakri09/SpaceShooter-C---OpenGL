#include "TogglePolygonSmoothEnabledEntry.h"


TogglePolygonSmoothEnabledEntry::TogglePolygonSmoothEnabledEntry(float xPos, float yPos, float zPos, float scale)
	:MenuEntry("Poly Smoothing: ", xPos, yPos, zPos, scale, false)
{
	newPolySmoothVal = glIsEnabled(GL_POLYGON_SMOOTH);
	prevPolySmoothVal = newPolySmoothVal;
	std::string enabledTxt;
	if(newPolySmoothVal)
	{
		enabledTxt = "enabled";
		EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
	}
	else
	{
		enabledTxt = "disabled";
		EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
	}
	EntryTransformable.SetXPos(EntryTransformable.getXPos()-20);
	valueTransformable = EntryTransformable;
	valueTransformable.SetXPos(valueTransformable.getXPos() + 30.0f);
}

TogglePolygonSmoothEnabledEntry::~TogglePolygonSmoothEnabledEntry()
{
}

void TogglePolygonSmoothEnabledEntry::OnClicked()
{
	newPolySmoothVal = !glIsEnabled(GL_POLYGON_SMOOTH);
}

void TogglePolygonSmoothEnabledEntry::UpdateEntry( float deltaTime )
{
	MenuEntry::UpdateEntry(deltaTime);
	
	UpdatePolySmoothValue();
}

void TogglePolygonSmoothEnabledEntry::DrawEntry()
{
	MenuEntry::DrawEntry();

	glPushMatrix();
	valueTransformable.ApplyGLTransformations(true, true, false);
	if(isSelected)
	{
		glColor4f( 0.898f, 0.694f, 0.227f, 1.0f);
	}
	else
	{
		glColor4f( 0.898f, 0.694f, 0.227f, 0.2f);
	}
	for(unsigned int i = 0; i < EntryValue->vboLetters.size(); i++)
	{
		glPushMatrix();

		EntryValue->vboLetters.at(i).stringPosition.ApplyGLTransformations(true, true, false);
		vbo.SetMeshInfo(EntryValue->vboLetters.at(i).meshInfo);
		vbo.Draw();

		glPopMatrix();
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPopMatrix();

}

void TogglePolygonSmoothEnabledEntry::UpdatePolySmoothValue()
{
	if(newPolySmoothVal != prevPolySmoothVal)
	{
		prevPolySmoothVal = newPolySmoothVal;
		std::string enabledTxt;
		if(newPolySmoothVal)
		{
			glEnable(GL_POLYGON_SMOOTH);
			enabledTxt = "enabled";
			EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
		}
		else
		{
			glDisable(GL_POLYGON_SMOOTH);
			enabledTxt = "disabled";
			EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
		}
	}
}
