/********************************************************************
    created:    2:11:2012   15:00
    filename:   ParticleEmitter.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ParticleEmitter_h__
#define ParticleEmitter_h__

#include <vector>
#include <memory>

#include "Particle.h"
#include "Logger.h"
#include "GetRandomFloat.h"

class ParticleEmitter
{
public:
    ParticleEmitter();
    ~ParticleEmitter();

	//Emmits a batch of particles. Origin is the start position of the particles,
	//particleAmnt is the amount of particles to emmit, startSpreadRadius defines
	//the area of which the particles can spawn away from the origin, max and min
	//speed defines the boundries for speed and the max and min life the boundries
	//for life which is affected by the fadeSpeed.
	void EmittParticles(Vector3D origin,
						unsigned int particleAmnt,
						float startSpreadRadius,
						float maxSpeed,
						float minSpeed,
						float maxLife,
						float minLife,
						float fadeSpeed);
protected:

private:
	Logger log;


	std::vector<std::shared_ptr<Particle>> particles;
};

#endif // ParticleEmitter_h__