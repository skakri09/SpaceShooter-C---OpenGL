/********************************************************************
	created:	12:11:2012   13:28
	filename: 	ToggleEffectsMute.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef ToggleEffectsMute_h__
#define ToggleEffectsMute_h__

#include "MenuEntry.h"
#include "SoundManager.h"

class ToggleEffectsMute : public MenuEntry
{
public:
	ToggleEffectsMute(float xPos, float yPos, float zPos,float scale);
	~ToggleEffectsMute();

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

#endif // ToggleEffectsMute_h__
