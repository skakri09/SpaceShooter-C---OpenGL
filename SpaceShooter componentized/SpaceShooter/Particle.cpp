#include "Particle.h"

#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;
Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::InitParticle(Vector3D startPos, Vector3D velocity, float fadeSpeed, 
							float r, float g, float b, float scale)
{
	life = 1.0f; 
	fade = fadeSpeed;

	Vector3D zerovec;
	transformation.Init(startPos, scale, velocity);

	this->r = r;
	this->g = g;
	this->b = b;
	CreateParticle("particle");
}

void Particle::Draw()
{
	if (IsAlive()) 
	{
		transformation.ApplyGLTransformations(true, true, false);
		//glColor4f(r, g, b, life);
		vbo.DrawWithArrays();
		//glColor4f(r, g, b, life);
		//glBegin(GL_QUADS);
		//glTexCoord2d(1,0); glVertex3f(position.getX()+0.5f,position.getY()+0.5f,position.getZ()); // Top Right
		//glTexCoord2d(0,0); glVertex3f(position.getX()-0.5f,position.getY()+0.5f,position.getZ()); // Top Left
		//glTexCoord2d(0,1); glVertex3f(position.getX()-0.5f,position.getY()-0.5f,position.getZ()); // Bottom Left
		//glTexCoord2d(1,1); glVertex3f(position.getX()+0.5f,position.getY()-0.5f,position.getZ()); // Bottom Right
		//glEnd();
	}
}

void Particle::Update( GLfloat deltaTime )
{
	transformation.Update(deltaTime);
	life -= fade * deltaTime;

	if (life <= 0.0f) 
	{
		FlagForKill();
	}
}

void Particle::CreateParticle( std::string particleNameNoExtension )
{
	if(!vbo.HaveMeshInfo())
	{
 		std::string basePath = "..//particles//";
 		std::string particleImgPath = basePath + particleNameNoExtension + ".png";
		std::string particleMeshpath = basePath + particleNameNoExtension + ".xml";
		
		Image img = ReadImage(particleImgPath);

		MeshInfo meshInfo = MeshFactory::Inst()->GetMesh(particleMeshpath);

		vbo.SetMeshInfo(meshInfo);
	}
}

Image Particle::ReadImage( std::string particleName )
{
	Image retImg;

	return retImg;
}
