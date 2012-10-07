/********************************************************************
    created:    6:10:2012   15:11
    filename:   GameConstants.h
    author:     Kristian Skarseth
    
    purpose:	A lame class for "the easy way out" ;)
				The class contains a few constants that are used
				by several classes.
*********************************************************************/
#ifndef GameConstants_H
#define GameConstants_H

static const float PLAYER_X_VELOCITY = 75.0f;
static const float PLAYER_Y_VELOCITY = 75.0f;
static const float PLAYER_Z_VELOCITY = 100.0f;

static const float FRUSTUM_LEFT = -90.0f;
static const float FRUSTUM_RIGHT = 90.0f;
static const float FRUSTUM_TOP = 0.0f;
static const float FRUSTUM_BOTTOM = -50.0f;

static const unsigned int window_width = 1280;
static const unsigned int window_height = 900;

#endif // GameConstants_H