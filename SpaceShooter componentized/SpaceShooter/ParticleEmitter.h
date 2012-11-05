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
#include "MeshFactory.h"
#include "Texturable.h"
#include "MeshInfo.h"
#include "MeshFactory.h"
#include "VBODrawable.h"

class ParticleEmitter : public Texturable
{
public:
    ParticleEmitter();
    ~ParticleEmitter();

	//Emits the given amount of particles. Origin is the center of the
	//particle emitting, where particles can spawn anywhere within the radius
	//of that point.
	void EmittParticles(Vector3D origin,
						unsigned int particleAmnt,
						float startSpreadRadius,
						float maxSpeed,
						float minSpeed,
						float fadeSpeed,
						float maxSize,
						float minSize,
						float r, float g, float b);

	void UpdateParticles(float deltaTime);

	void DrawParticles();

private:
	Logger log;

	std::vector<std::shared_ptr<Particle>> particles;

	VBODrawable vbo;

};

#endif // ParticleEmitter_h__