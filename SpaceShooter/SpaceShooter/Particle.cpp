#include "Particle.h"

#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;
Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::InitParticle(Vector3D startPos, Vector3D velocity, 
							float fadeSpeed, float r, float g, float b, float scale)
{
	life = 1.0f; 
	fade = fadeSpeed;

	transformation.Init(startPos, scale, velocity);

	this->r = r;
	this->g = g;
	this->b = b;
}

void Particle::Draw()
{
	if (IsAlive()) 
	{
		transformation.ApplyGLTransformations(true, true, false);
		glColor4f(r, g, b, life);
	}
}

void Particle::Update( GLfloat deltaTime )
{
	transformation.Update(deltaTime);

	life -= fade * deltaTime;

	if (life <= 0.00f) 
	{
		life = 0.0f;
		FlagForKill();
	}
}