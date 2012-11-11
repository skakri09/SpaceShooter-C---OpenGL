/********************************************************************
    created:    11:11:2012   21:32
    filename:   SMPEGPlayer.h
    author:     Kristian Skarseth
    
	purpose:	A wrapper class for Loki softwares SMPEG library. Can load
	and play a MPEG-1 video file. 

	Note:		The code is based on Drew_benton's code from GameDev.net.
	The original code can be found here:
	http://www.gamedev.net/topic/348340-play-video-files-in-sdl/
*********************************************************************/

#ifndef SMPEG_PLAYER_H
#define SMPEG_PLAYER_H

#include <SDL.h>
#include <smpeg.h>

#include "Logger.h"
#include "SoundManager.h"

using std::endl;
using std::string;

class SMPEGPlayer
{
public:
	//void PlayMovie();
	SMPEGPlayer();

	// Free our movie
	~SMPEGPlayer();

	void ClearScreen();
	void SetVolume( int vol );// Set's the volume on a scale of 0 - 100
	void Scale( int w, int h );
	void ScaleBy( int factor );

	// Sets the region of the video to be shown
	void SetDisplayRegion( int x, int y, int w, int h );

	// Set the position that the movie should be drawn at on the screen
	void SetPosition( int x, int y );

	// Load the movie
	bool Load( string fileName, SDL_Surface* renderEngineScreen, int maxscalex = 1, int maxscaley = 1 );

	// Set the looping of the movie
	void SetLoop( int val );

	void Play();
	void Pause();
	void Stop();

	void Rewind();					// Rewind the movie back to 0:00:00
	void Seek( int bytes );			// Seek a number of bytes into the movie
	void Skip( float seconds );		// Skip a number of seconds
	void RenderFrame( int frame );	// Render some frame of the movie
	void RenderFinal();				// Render the final frame of the movie
	void DisplayAt( int x, int y );	// Draw the movie surface to the main screen at x, y
	void Display();					// Draw the movie surface to the main screen at x, y
	SMPEG_Info GetInfo();			// Return the current info for the movie

	// Get the current status of the movie, can be SMPEG_ERROR = -1, SMPEG_STOPPED, SMPEG_PLAYING
	SMPEGstatus GetStatus();

private:
	Logger log;

	// Surface for the main screen
	SDL_Surface *screen;

	// Surface for the movie
	SDL_Surface *movieSurface;

	// Holds the movie information
	SMPEG_Info movieInfo;

	// Load the movie
	SMPEG *movie;

	// The max we can scale by
	int MaxScaleX;
	int MaxScaleY;
	int MaxScale;

	// Locations on screen to draw at
	int X, Y;

	void DrawIMG(SDL_Surface *img, SDL_Surface *dst, int x, int y);
};

#endif