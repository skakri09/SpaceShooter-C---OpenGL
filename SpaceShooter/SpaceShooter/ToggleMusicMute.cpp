#include "ToggleMusicMute.h"


ToggleMusicMute::ToggleMusicMute(float xPos, float yPos, float zPos, float scale)
	: MenuEntry("music mute:",xPos, yPos, zPos, scale)
{
	newSoundMuteVal = SoundManager::Inst()->SoundMuted();
	prevSoundMuteVal = newSoundMuteVal;
	std::string enabledTxt;
	if(newSoundMuteVal)
	{
		enabledTxt = "on";
		EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
	}
	else
	{
		enabledTxt = "off";
		EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
	}
	EntryTransformable.SetXPos(EntryTransformable.getXPos()-5);
	valueTransformable = EntryTransformable;
	valueTransformable.SetXPos(valueTransformable.getXPos() + 25.0f);
}

ToggleMusicMute::~ToggleMusicMute()
{
}

void ToggleMusicMute::OnClicked()
{
	newSoundMuteVal = !SoundManager::Inst()->MusicMuted();
}

void ToggleMusicMute::UpdateEntry( float deltaTime )
{
	MenuEntry::UpdateEntry(deltaTime);

	UpdateSoundMuteVal();
}

void ToggleMusicMute::DrawEntry()
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

void ToggleMusicMute::UpdateSoundMuteVal()
{
	if(newSoundMuteVal != prevSoundMuteVal)
	{
		prevSoundMuteVal = newSoundMuteVal;
		std::string enabledTxt;
		if(newSoundMuteVal)
		{
			SoundManager::Inst()->SetMusicMute(true);
			enabledTxt = "on";
			EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
		}
		else
		{
			SoundManager::Inst()->SetMusicMute(false);
			enabledTxt = "off";
			EntryValue = TextFactory::Inst()->GetVboString(&enabledTxt);
		}
	}
}