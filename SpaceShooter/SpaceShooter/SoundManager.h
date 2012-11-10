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

class SoundManager
{
public:
    static SoundManager* Inst();

	void InitSoundManager();

	void PlaySong(std::string songName);

	void PlayEffect(std::string effectName);

private:
	SoundManager();
	~SoundManager();

	std::string songBasePath;
	std::string effectBasePath;

	std::map<std::string, Mix_Music*> Songs;
	std::map<std::string, Mix_Chunk*> Effects;

};

#endif // SoundManager_h__