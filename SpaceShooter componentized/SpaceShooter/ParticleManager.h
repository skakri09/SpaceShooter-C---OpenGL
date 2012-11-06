/********************************************************************
    created:    5:11:2012   20:53
    filename:   ParticleManager.h
    author:     Kristian Skarseth
    
    purpose:    Takes care of all particles in the game. Spaceships or other 
				components in need of displaying a particle-something use
				this class.
*********************************************************************/
#ifndef ParticleManager_h__
#define ParticleManager_h__

#include <memory>
#include <vector>

#include "Vector3d.h"
#include "GetRandomFloat.h"
#include "MeshFactory.h"
#include "VBODrawable.h"
#include "Particle.h"

class ParticleManager
{
public:
	//Singleton access function
   static ParticleManager* Inst();

   //Should preload meshes or images used by the particle manager
   void InitParticleManager();

   void DrawParticles();
   void UpdateParticles(float deltaTime);

   //Emits a batch of particles that can be used for a standard collision
   void EmitStandardSpaceshipProjectileCollision(Vector3D origin);
  
   //Function to emit a custom batch of particles
   void EmitParticles(Vector3D origin,
	   unsigned int particleAmnt,
	   float startSpreadRadius,
	   float maxSpeed,
	   float fadeSpeed,
	   float maxSize,
	   float minSize,
	   float r, float g, float b);

private:
	ParticleManager();
	~ParticleManager();

	VBODrawable vbo;

	std::vector<std::shared_ptr<Particle>> particles;
};

#endif // ParticleManager_h__