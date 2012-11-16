/********************************************************************
    created:    10:11:2012   22:08
    filename:   SoundManager.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SoundManager_h__
#define SoundManager_h__

#include <sdl.h>
#include <SDL_mixer.h>
#include <string>
#include <map>
#include <sstream>

#include "ManagerInterface.h"


class SoundManager : public ManagerInterface
{
public:
    static SoundManager* Inst();

	void InitSoundManager();

	void PlaySong(std::string songName, unsigned short volume = 100);

	void PlayEffect(std::string effectName, unsigned short volume = 100);
	void PlayEffect(unsigned int channel, 
					std::string effectName, 
					unsigned short volume = 100);

	void Update(float deltaTime);

	bool SoundMuted();
	void SetSoundMute(bool mute);

	bool MusicMuted();
	void SetMusicMute(bool mute);

	bool EffectsMuted();
	void SetEffectsMuted(bool mute);

private:
	SoundManager();
	~SoundManager();

	std::string songBasePath;
	std::string effectBasePath;

	std::map<std::string, Mix_Music*> Songs;
	std::map<std::string, Mix_Chunk*> Effects;

	static const unsigned short FX_MAIN_CHANNEL = 1;

	bool soundMuted;
	bool musicMuted;
	bool effectsMuted;

	std::string currentPlayedMusic;
	unsigned short currentSongVolume;

	std::string currentPlayedMusic_global;
	unsigned short currentSongVolume_global;


	std::string songPlayedPreMute;
	unsigned short prevSongVolume;


	std::string songPlayedPreMute_global;
	unsigned short prevSongVolume_global;
};

#endif // SoundManager_h__