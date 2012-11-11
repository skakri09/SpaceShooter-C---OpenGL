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

static const float FRUSTUM_LEFT = -35.0f;
static const float FRUSTUM_RIGHT = 35.0f;
static const float FRUSTUM_TOP = 20.0f;
static const float FRUSTUM_BOTTOM = -22.0f;
static const float FRUSTUM_DEPTH = 1200.0f;
static const float CAMERA_POS_X = 0.0f;
static const float CAMERA_POS_Y = 0.0f;
static const float CAMERA_POS_Z = 30.0f;
static const unsigned int window_width = 1280;
static const unsigned int window_height = 720;

#endif // GameConstants_H