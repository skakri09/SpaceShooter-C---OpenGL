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

	void Update(float deltaTime){}

private:
	SoundManager();
	~SoundManager();

	std::string songBasePath;
	std::string effectBasePath;

	std::map<std::string, Mix_Music*> Songs;
	std::map<std::string, Mix_Chunk*> Effects;

	static const unsigned short MUS_MAIN_CHANNEL = 1;
	static const unsigned short FX_MAIN_CHANNEL = 2;
};

#endif // SoundManager_h__