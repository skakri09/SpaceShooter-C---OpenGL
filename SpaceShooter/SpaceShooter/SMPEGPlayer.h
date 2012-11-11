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

using std::endl;
using std::string;

class CSmpeg
{
public:
	//void PlayMovie();
	CSmpeg();

	// Free our movie
	~CSmpeg();

	void ClearScreen();

	// Set's the volume on a scale of 0 - 100
	void SetVolume( int vol );

	// Scale the movie by the desired factors
	void Scale( int w, int h );

	// Scale the movie by the desired factor
	void ScaleBy( int factor );

	// Sets the region of the video to be shown
	void SetDisplayRegion( int x, int y, int w, int h );

	// Set the position that the movie should be drawn at on the screen
	void SetPosition( int x, int y );

	// Load the movie
	bool Load( string fileName, SDL_Surface* renderEngineScreen, int maxscalex = 1, int maxscaley = 1 );

	// Set the looping of the movie
	void SetLoop( int val );

	// Play the movie
	void Play();

	// Pause the movie
	void Pause();

	// Stops the movie, but keeps current position
	void Stop();

	// Rewind the movie back to 0:00:00
	void Rewind();

	// Seek a number of bytes into the movie
	void Seek( int bytes );

	// Skip a number of seconds
	void Skip( float seconds );

	// Render some frame of the movie
	void RenderFrame( int frame );

	// Render the final frame of the movie
	void RenderFinal();

	// Draw the movie surface to the main screen at x, y
	void DisplayAt( int x, int y );

	// Draw the movie surface to the main screen at x, y
	void Display();

	// Return the current info for the movie
	SMPEG_Info GetInfo();

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