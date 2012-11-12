/********************************************************************
	created:	12:11:2012   12:51
	filename: 	ToggleMusicMute.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef ToggleMusicMute_h__
#define ToggleMusicMute_h__

#include "MenuEntry.h"
#include "SoundManager.h"

class ToggleMusicMute : public MenuEntry
{
public:
	ToggleMusicMute(float xPos, float yPos, float zPos,float scale);
	~ToggleMusicMute();

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

#endif // ToggleMusicMute_h__
