#include "ParticleEmitter.h"


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
									float maxLife, 
									float minLife,
									float fadeSpeed )
{
	unsigned int newVecSize = particles.size() + particleAmnt;
	particles.reserve(newVecSize);

	for(int i = particles.size(); i <newVecSize; i++)
	{
		particles[i] = std::make_shared<Particle>();
		
		Vector3D startPos(origin.getX()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
						origin.getY()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
						origin.getZ()+GetRandFloat(-startSpreadRadius, startSpreadRadius));

		Vector3D velocity(GetRandFloat(minSpeed, maxSpeed),
						GetRandFloat(minSpeed, maxSpeed),
						GetRandFloat(minSpeed, maxSpeed));

		particles[i]->InitParticle(startPos, velocity, fadeSpeed, );
	}
}
