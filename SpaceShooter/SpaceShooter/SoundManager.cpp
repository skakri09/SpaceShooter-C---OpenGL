#include "SoundManager.h"


SoundManager::SoundManager()
{
	songBasePath = "..//Sound//Songs//";
	effectBasePath = "..//Sound//Effects//";
}

SoundManager::~SoundManager()
{
}

void SoundManager::InitSoundManager()
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		std::stringstream err;
		err << "Could not initialize soundManager: " << SDL_GetError();
		throw std::runtime_error(err.str());
	}
	Effects["laser"] = Mix_LoadWAV((effectBasePath+"laser.wav").c_str());
	Effects["laser_short"] = Mix_LoadWAV((effectBasePath+"laser_short.wav").c_str());
	Effects["blaster"] = Mix_LoadWAV((effectBasePath+"blaster.wav").c_str());
	Effects["button"] = Mix_LoadWAV((effectBasePath+"button.wav").c_str());
	Effects["laser_tripleFire_long"] = Mix_LoadWAV( (effectBasePath+"laser_tripleFire_long.wav").c_str());

	Songs["imperial_march"] = Mix_LoadMUS( (songBasePath+"imperial_march.ogg").c_str());
}

SoundManager* SoundManager::Inst()
{
	static SoundManager* instance = new SoundManager();
	return instance;
}

void SoundManager::PlaySong( std::string songName, unsigned short volume )
{
	Mix_Music* song;
	if(Songs.find(songName) != Songs.end())
	{
		song = Songs.find(songName)->second;
	}
	else
	{
		song = Mix_LoadMUS( (songBasePath+songName+".ogg").c_str());
		Songs[songName] = song;
		
	}
	Mix_HaltMusic();
	Mix_PlayMusic(song, -1);
}

void SoundManager::PlayEffect( std::string effectName, unsigned short volume )
{
	Mix_Chunk* effect;
	if(Effects.find(effectName) != Effects.end())
	{
		effect = Effects.find(effectName)->second;
	}
	else
	{
		 effect = Mix_LoadWAV((effectBasePath+effectName+".wav").c_str());
		 Effects[effectName] = effect;
	}
	Mix_HaltChannel(FX_MAIN_CHANNEL);
	Mix_PlayChannel(FX_MAIN_CHANNEL, effect, 0);
	Mix_Volume(FX_MAIN_CHANNEL, volume);
}

