#include "SmpegPlayer.h"


/*  P U B L I C     F U N C T I O N S  */
/*  ---------------------------------  */

SmpegPlayer::SmpegPlayer() : log("SmpegPlayer", INFO)
{
	MaxScaleX = MaxScaleY = MaxScale = 1;

	screen = 0;
	movieSurface = 0;
	movie = 0;
	X = Y = 0;

}

// Free our movie
SmpegPlayer::~SmpegPlayer()
{
	
	if(movie)
	{
		Stop();
		SMPEG_delete( movie );
		movie = 0;
	}
	SDL_FreeSurface( movieSurface );
	movieSurface = 0;
}

void SmpegPlayer::ClearScreen()
{
	SDL_FillRect( movieSurface, 0, 0 );
}

// Set's the volume on a scale of 0 - 100
void SmpegPlayer::SetVolume( int vol )
{
	SMPEG_setvolume( movie, vol );
}

// Scale the movie by the desired factors
void SmpegPlayer::Scale( int w, int h )
{
	// Prevent a divide by 0
	if( w == 0 )
		w = 1;
	if( h == 0 )
		h = 1;

	SMPEG_scaleXY( movie, w, h );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "Scale() - SMPEG_scaleXY() error: " << SMPEG_error(movie) << endl;
}

// Scale the movie by the desired factor
void SmpegPlayer::ScaleBy( int factor )
{
	// Prevent a divide by 0
	if( factor == 0 )
		factor = 1;
	// Make sure we don't scale larger than the surface size
	if( factor > MaxScale )
		factor = MaxScale;

	SMPEG_scale( movie, factor );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "ScaleBy() error: "<< SMPEG_error(movie) << endl;
}

// Sets the region of the video to be shown
void SmpegPlayer::SetDisplayRegion( int x, int y, int w, int h )
{
	SMPEG_setdisplayregion( movie, x, y, w, h );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "SetDisplayRegion() error: " << SMPEG_error(movie) << endl;
}

// Set the position that the movie should be drawn at on the screen
void SmpegPlayer::SetPosition( int x, int y )
{
	X = x;
	Y = y;
}

// Load the movie
bool SmpegPlayer::Load( string fileName, SDL_Surface* renderEngineScreen, int maxscalex, int maxscaley )
{
	MaxScaleX = maxscalex;
	MaxScaleY = maxscaley;

	// Limit how much we can scale by
	MaxScale = (maxscalex > maxscaley ? maxscaley : maxscalex);

	// Assign the screen surface
	screen = renderEngineScreen;

	if(movie)
	{
		SMPEG_delete( movie );
		movie = 0;
	}
	if( fileName != "")
	{
		movie = SMPEG_new(fileName.c_str(), &movieInfo, true );
	}
	else
	{
		return false;
	}
	if(SMPEG_error(movie) != NULL)
	{
		log << WARN << "Load() - SMPEG_new() error: " << SMPEG_error(movie) << endl;
	}
	else
	{
		currentlyLoadedVideo = fileName;
	}


	// Create a temporary surface to render the movie to
	SDL_Surface* tempSurface2 = SDL_CreateRGBSurface( SDL_SWSURFACE, movieInfo.width * MaxScaleX, movieInfo.height * MaxScaleY, 32, screen->format->Rmask, 
		screen->format->Gmask, screen->format->Bmask, screen->format->Amask );

	// Now make a surface optimized for the main screen
	movieSurface = SDL_DisplayFormat( tempSurface2 );

	// Free the temporary surface
	SDL_FreeSurface( tempSurface2 );

	// Set the surface to draw to
	SMPEG_setdisplay( movie, movieSurface, 0, 0 );
	if(SMPEG_error(movie) != NULL)
	{
		log << WARN << "Load() - SMPEG_setdisplay() error: " << SMPEG_error(movie) << endl;
		return false;
	}


	// Set the display region
	SMPEG_setdisplayregion( movie, 0, 0, movieInfo.width, movieInfo.height );
	if(SMPEG_error(movie) != NULL)
	{
		log << WARN << "Load() - SMPEG_setdisplayregion() error: " << SMPEG_error(movie) << endl;
	}
	return true;
}

// Set the looping of hte movie
void SmpegPlayer::SetLoop( int val )
{
	SMPEG_loop( movie, val );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "SetLoop() error: " << SMPEG_error(movie) << endl;
}

// Play the movie
void SmpegPlayer::Play()
{
	SMPEG_play( movie );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "Play() error: " << SMPEG_error(movie) << endl;
}

// Pause the movie
void SmpegPlayer::Pause()
{
	SMPEG_pause( movie );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "Pause() error: " << SMPEG_error(movie) << endl;
}

// Stops the movie, but keeps current position
void SmpegPlayer::Stop()
{
	SMPEG_stop( movie );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "Stop() error: " << SMPEG_error(movie) << endl;
}

// Rewind the movie back to 0:00:00
void SmpegPlayer::Rewind()
{
	SMPEG_rewind( movie );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "Rewind() error: " << SMPEG_error(movie) << endl;
}

// Seek a number of bytes into the movie
void SmpegPlayer::Seek( int bytes )
{
	SMPEG_seek( movie, bytes );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "Rewind() error: " << SMPEG_error(movie) << endl;
}

// Skip a number of seconds
void SmpegPlayer::Skip( float seconds )
{
	SMPEG_skip( movie, seconds );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "Skip() error: " << SMPEG_error(movie) << endl;
}

// Render some frame of the movie
void SmpegPlayer::RenderFrame( int frame )
{
	SMPEG_renderFrame( movie, frame );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "RenderFrame() error: " << SMPEG_error(movie) << endl;
}

// Render the final frame of the movie
void SmpegPlayer::RenderFinal()
{
	SMPEG_renderFinal( movie, movieSurface, 0, 0 );
	if(SMPEG_error(movie) != NULL)
		log << WARN << "RenderFinal() error: " << SMPEG_error(movie) << endl;
}

// Draw the movie surface to the main screen at x, y
void SmpegPlayer::DisplayAt( int x, int y )
{
	DrawIMG( movieSurface, screen, x, y );
}

// Draw the movie surface to the main screen at x, y
void SmpegPlayer::Display()
{
	DrawIMG( movieSurface, screen, X, Y );
}

// Return the current info for the movie
SMPEG_Info SmpegPlayer::GetInfo()
{
	SMPEG_getinfo( movie, &movieInfo );
	return movieInfo;
}

// Get the current status of the movie, can be SMPEG_ERROR = -1, SMPEG_STOPPED, SMPEG_PLAYING
SMPEGstatus SmpegPlayer::GetStatus()
{
	if(movie)
	{
		return SMPEG_status(movie);
	}
	return SMPEG_STOPPED;
}


/*  P R I V A T E     F U N C T I O N S  */
/*   ----------------------------------  */
void SmpegPlayer::DrawIMG(SDL_Surface *img, SDL_Surface *dst, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(img, NULL, dst, &dest);
}