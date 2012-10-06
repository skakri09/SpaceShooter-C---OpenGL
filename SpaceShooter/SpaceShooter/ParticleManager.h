/********************************************************************
    created:    5:10:2012   16:11
    filename:   ParticleManager.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ParticleManager_h__
#define ParticleManager_h__
#ifdef _WIN32
#include <windows.h>
#endif
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <gl/GL.h>
#include "Particle.h"
#include "Logger.h"


struct Image {
	std::vector<char> data;
	unsigned int components;
	unsigned long width;
	unsigned long height;
};

//struct Particle {
//	bool	active;					// Active (Yes/No)
//	float	life;					// Particle Life
//	float	fade;					// Fade Speed
//	float	r;						// Red Value
//	float	g;						// Green Value
//	float	b;						// Blue Value
//	float	x;						// X Position
//	float	y;						// Y Position
//	float	z;						// Z Position
//	float	xi;						// X Direction
//	float	yi;						// Y Direction
//	float	zi;						// Z Direction
//};

// const value for the maximum number of lightspeed particles
static const unsigned int MAX_LIGHTPSEED_PARTICLES = 1000;

//The max distance a star can spawn from the middle and in 
// x/y direction
static const float MAX_STAR_DIST_FROM_MIDDLE_X = 350.0f;
static const float MAX_STAR_DIST_FROM_MIDDLE_Y = 250.0f;
static const float STAR_FARPOINT = -300.0f;
class ParticleManager
{
public:
    ParticleManager();
    ~ParticleManager();

	void InitParticleManager();

	void UpdateAndDrawParticles(GLfloat deltatime );

protected:

private:
	Logger log;
	void InitDevil();

	std::vector<Particle> LightspeedStars;

	GLuint particle1;
	void InitLightspeedStars();

	float GetRandFloat(float min, float max);

	Image ReadImage(std::string image);

	Vector3D zeroPoint;
};

#endif // ParticleManager_h__