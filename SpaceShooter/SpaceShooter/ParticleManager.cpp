#include "ParticleManager.h"

ParticleManager::ParticleManager()
	:log("ParticleManager", WARN)
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
	for(unsigned int i = 0; i < MAX_PARTICLES; i++)
	{
		InactiveParticles.push_back(new Particle());
		InactiveParticles.back()->FlagForKill();
	}
}


void ParticleManager::DrawParticles()
{
	if(!ActiveParticles.empty())
	{
		if(vbo.HaveMeshInfo())
		{
			glColor3f(1.0f, 0.5f, 1.0f);
			vbo.EnableClientStates();
			for(auto i = ActiveParticles.begin(); i != ActiveParticles.end(); i++)
			{
				if( (*i)->IsAlive() )
				{
					glPushMatrix();
					(*i)->Draw();	 // Applies particle-specific translation etc
					vbo.Draw(false); // Draws the particle with the shared VBO
					glPopMatrix();
				}
			}
			vbo.DisableClientStates();
			glColor4f(1, 1, 1, 1);
		}
	}
	//if(!particles.empty())
	//{
	//	if(vbo.HaveMeshInfo())
	//	{
	//		glColor3f(1.0f, 0.5f, 1.0f);
	//		vbo.EnableClientStates();
	//		for(auto i = particles.begin(); i != particles.end(); i++)
	//		{
	//			if( (*i)->IsAlive() )
	//			{
	//				glPushMatrix();
	//				(*i)->Draw();	 // Applies particle-specific translation etc
	//				vbo.Draw(false); // Draws the particle with the shared VBO
	//				glPopMatrix();
	//			}
	//		}
	//		vbo.DisableClientStates();
	//		glColor4f(1, 1, 1, 1);
	//	}
	//}
}

void ParticleManager::Update( float deltaTime )
{
	if(!ActiveParticles.empty())
	{
		for(auto i = ActiveParticles.begin(); i != ActiveParticles.end();)
		{
			(*i)->Update(deltaTime);

			if((*i)->CanKill())
			{
				i = ActiveParticles.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
	/*
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
	 }*/
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
	unsigned int x = 0;

	for(unsigned int i = 0; i <particleAmnt; i++)
	{	
		bool foundParticle = false;
		while(!foundParticle)
		{
			if(x < InactiveParticles.size())
			{
				if(!InactiveParticles.at(x)->IsAlive())
				{
					ActiveParticles.push_back(InactiveParticles.at(x));
					Vector3D startPos(origin.getX()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
						origin.getY()+GetRandFloat(-startSpreadRadius, startSpreadRadius),
						origin.getZ()+GetRandFloat(-startSpreadRadius, startSpreadRadius));
					Vector3D velocity(GetRandFloat(-maxSpeed, maxSpeed),
						GetRandFloat(-maxSpeed, maxSpeed),
						GetRandFloat(-maxSpeed, maxSpeed));
					float scale = GetRandFloat(minSize, maxSize);
					ActiveParticles.back()->InitParticle(startPos, velocity, fadeSpeed, r, g, b, scale );
					foundParticle = true;
				}
				++x;
			}
			else 
			{
				log << CRITICAL << "More particles active then allowed" << std::endl;
				i = particleAmnt;
				break;
			}
		}

	}
/*
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
	}*/
}

void ParticleManager::ResetParticles()
{
	for(auto i = ActiveParticles.begin(); i != ActiveParticles.end(); i++)
	{
		Particle* p = *i;
		i = ActiveParticles.erase(i);
		delete p;
		p = 0;
	}
	particles.clear();
}

