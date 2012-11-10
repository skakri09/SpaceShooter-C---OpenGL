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

}

SoundManager* SoundManager::Inst()
{
	static SoundManager* instance = new SoundManager();
	return instance;
}

void SoundManager::PlaySong( std::string songName )
{

}

void SoundManager::PlayEffect( std::string effectName )
{

}

