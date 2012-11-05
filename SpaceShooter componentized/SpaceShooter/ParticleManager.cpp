#include "ParticleManager.h"

ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}

ParticleManager* ParticleManager::Inst()
{
	static ParticleManager* instance = new ParticleManager();
	return instance;
}

void ParticleManager::InitParticleManager()
{
	if(!vbo.HaveMeshInfo())
	{
		vbo.SetMeshInfo(MeshFactory::Inst()->GetMesh("..//particles//particle.xml"));
	}
}


void ParticleManager::DrawParticles()
{
	if(!particles.empty())
	{
		//BindTexture("particle");
		for(auto i = particles.begin(); i != particles.end(); i++)
		{
			if(vbo.HaveMeshInfo())
			{
				glPushMatrix();
				(*i)->Draw();
				vbo.DrawWithArrays();
				glPopMatrix();
			}
		}
		glColor4f(1, 1, 1, 1);
	}
}

void ParticleManager::UpdateParticles( float deltaTime )
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


void ParticleManager::EmitStandardSpaceshipProjectileCollision( Vector3D origin )
{
	float g = 1.0f;//GetRandFloat(0.2f, 0.8f);
	EmitParticles(origin, 100, 0.1f, 10, 1.0f, 0.3f, 0.1f, 1.0f, g, 1.0f);
}


void ParticleManager::EmitParticles( Vector3D origin, 
	unsigned int particleAmnt, 
	float startSpreadRadius, 
	float maxSpeed, 
	float fadeSpeed,
	float maxSize,
	float minSize,
	float r, float g, float b)
{
	unsigned int newVecSize = particles.size() + particleAmnt;
	particles.reserve(newVecSize);

	for(unsigned int i = 0; i <particleAmnt; i++)
	{
		particles.push_back(std::make_shared<Particle>());

		Vector3D startPos(origin.getX()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
			origin.getY()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
			origin.getZ()+GetRandFloat(-startSpreadRadius, startSpreadRadius));

		Vector3D velocity(GetRandFloat(-maxSpeed, maxSpeed),
			GetRandFloat(-maxSpeed, maxSpeed),
			GetRandFloat(-maxSpeed, maxSpeed));

		float scale = GetRandFloat(minSize, maxSize);

		particles.back()->InitParticle(startPos, velocity, fadeSpeed, r, g, b, scale );
	}
}

