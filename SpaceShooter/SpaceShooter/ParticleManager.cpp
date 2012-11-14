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
		glColor3f(1.0f, 0.5f, 1.0f);
		for(auto i = particles.begin(); i != particles.end(); i++)
		{
			if(vbo.HaveMeshInfo())
			{
				glPushMatrix();
				(*i)->Draw();	//Applies particle-specific translation etc
				vbo.Draw();		//Draws the particle with the shared VBO
				glPopMatrix();
			}
		}
		glColor4f(1, 1, 1, 1);
	}
}

void ParticleManager::Update( float deltaTime )
{
	if(!particles.empty())
	{

		for(auto i = particles.begin(); i != particles.end();)
		{
			(*i)->Update(deltaTime);

			if((*i)->CanKill())
			{
				i = particles.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
}

void ParticleManager::EmitStandardSpaceshipProjectileCollision( Vector3D origin )
{
	EmitParticles(origin, 30, 0.1f, 10, 1.0f, 0.3f, 0.1f, 1.0f, 0.5f, 0.0f);
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

void ParticleManager::ResetParticles()
{
	particles.clear();
}

