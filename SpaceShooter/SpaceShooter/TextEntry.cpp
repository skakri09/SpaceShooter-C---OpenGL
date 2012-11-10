#include "TextEntry.h"


TextEntry::TextEntry()
{
}

void TextEntry::Update( float deltaTime )
{
	if(updatedString != stringInUse)
	{
		stringInUse = updatedString;
		VBOString = TextFactory::Inst()->GetVboString(&stringInUse);
	}
}

void TextEntry::Draw(VBODrawable* vbo)
{
	glPushMatrix();
	GUIEntry::transformable.ApplyGLTransformations(true, true, true);

	for(unsigned int i = 0; i < VBOString->vboLetters.size(); i++)
	{
		glPushMatrix();

		VBOString->vboLetters.at(i).stringPosition.ApplyGLTransformations(true, true, false);
		vbo->SetMeshInfo(VBOString->vboLetters.at(i).meshInfo);
		vbo->Draw();

		glPopMatrix();
	}

	glPopMatrix();
}
