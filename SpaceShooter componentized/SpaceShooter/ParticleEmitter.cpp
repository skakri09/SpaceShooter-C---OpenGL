#include "ParticleEmitter.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;

ParticleEmitter::ParticleEmitter()
	:log("ParticleEmitter", WARN)
{
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::EmittParticles( Vector3D origin, 
									unsigned int particleAmnt, 
									float startSpreadRadius, 
									float maxSpeed, 
									float minSpeed, 
									float fadeSpeed,
									float maxSize,
									float minSize,
									float r, float g, float b)
{
	unsigned int newVecSize = particles.size() + particleAmnt;
	particles.reserve(newVecSize);

	for(unsigned int i = (newVecSize-particleAmnt); i <newVecSize; i++)
	{
		//particles[i] = std::make_shared<Particle>();
		particles.push_back(std::make_shared<Particle>());
		Vector3D startPos(origin.getX()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
						origin.getY()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
						origin.getZ()+GetRandFloat(-startSpreadRadius, startSpreadRadius));

		Vector3D velocity(GetRandFloat(minSpeed, maxSpeed),
						GetRandFloat(minSpeed, maxSpeed),
						GetRandFloat(minSpeed, maxSpeed));

		float scale = GetRandFloat(minSize, maxSize);

		particles.back()->InitParticle(startPos, velocity, fadeSpeed, r, g, b, scale );
		//particles[i]->InitParticle(startPos, velocity, fadeSpeed, r, g, b, scale );
	}
}

void ParticleEmitter::UpdateParticles( float deltaTime )
{
	if(!particles.empty())
	{
		for(auto i = particles.begin(); i != particles.end();)
		{
			if((*i)->CanKill())
			{
				i = particles.erase(i);
			}
			else
			{
				(*i)->Update(deltaTime);
				++i;
			}

		}
	}
}

void ParticleEmitter::DrawParticles()
{
	if(!particles.empty())
	{
		//glEnable(GL_COLOR);
		//BindTexture("particle");
		for(auto i = particles.begin(); i != particles.end(); i++)
		{
			(*i)->Draw();
		}
		glColor4f(1, 1, 1, 1);
		//glDisable(GL_COLOR);
		//UnbindTexture();
	}
}
