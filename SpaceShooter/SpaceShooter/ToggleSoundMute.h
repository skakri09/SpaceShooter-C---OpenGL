/********************************************************************
	created:	12:11:2012   10:39
	filename: 	ToggleSoundMute.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef ToggleSoundMute_h__
#define ToggleSoundMute_h__

#include "MenuEntry.h"
#include "SoundManager.h"

class ToggleSoundMute : public MenuEntry
{
public:
	ToggleSoundMute(float xPos, float yPos, float zPos,float scale);
	~ToggleSoundMute();

	void OnClicked();

	void UpdateEntry(float deltaTime);

	void DrawEntry();

protected:

private:
	std::shared_ptr<VboString> EntryValue;
	Transformable valueTransformable;
	void UpdateSoundMuteVal();
	GLboolean prevSoundMuteVal;
	GLboolean newSoundMuteVal;
};

#endif // ToggleSoundMute_h__
