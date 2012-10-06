/********************************************************************
    created:    5:10:2012   14:26
    filename:   Particle.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Particle_h__
#define Particle_h__

#ifdef _WIN32
#include <windows.h>
#endif
#include <vector>
#include <gl/GL.h>
#include "Vector3d.h"

class Particle
{
public:
    Particle();
    ~Particle();


	void InitParticle(Vector3D StartPos, Vector3D Velocity, 
					float fadeSpeed, float r, float g, float b);

	void UpdateParticle(GLfloat deltatime);

	void DrawParticle();


	bool isActive; //Is the particle active
	float life;  //The life of the particle
	float fade;  //The fade speed of the particle (fade value is substracted from life)
	
	float r;     //Red color value
	float g;	 //Green color value
	float b;	 //Blue color value
	
	Vector3D position;
	Vector3D velocity;

protected:

private:

};

#endif // Particle_h__