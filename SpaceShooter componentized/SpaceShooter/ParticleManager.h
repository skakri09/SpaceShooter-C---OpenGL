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
#include "Particle.h"
#include "GameConstants.h"
#include "Image.h"
#include "GetRandomFloat.h"
#include <gl/GL.h> //must be included after particle.h

#include "Logger.h"


// const value for the maximum number of lightspeed particles
static const unsigned int MAX_LIGHTPSEED_PARTICLES = 1000;

//The max distance a star can spawn from the middle and in 
// x/y direction
static const float MAX_STAR_DIST_FROM_MIDDLE_X = 650.0f;
static const float MAX_STAR_DIST_FROM_MIDDLE_Y = 450.0f;
static const float STAR_FARPOINT = -550.0f;

class ParticleManager
{
public:
    ParticleManager();
    ~ParticleManager();

	void InitParticleManager();

	void UpdateParticles(GLfloat deltatime);

	void DrawParticles();

protected:

private:
	Logger log;
	void InitDevil();

	std::vector<Particle> LightspeedStars;

	GLuint particle1;
	void InitLightspeedStars();

	Image ReadImage(std::string image);

	Vector3D zeroPoint;

	void InitNewLightspeedParticle(Particle& p, bool firstFrame);
	bool validLightspeedPos(float xPos, float yPos);
	int failcounter;
};

#endif // ParticleManager_h__