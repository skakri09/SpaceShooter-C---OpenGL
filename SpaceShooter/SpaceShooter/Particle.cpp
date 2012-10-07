#include "Particle.h"


Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::InitParticle(Vector3D startPos, Vector3D velocity, 
							float fadeSpeed, float r, float g, float b)
{
	isActive = true;	
	life = 1.0f; 
	fade = fadeSpeed; //rand()/static_cast<float>(RAND_MAX)+0.1f;	// Random Fade Speed

	this->position = startPos;

	this->velocity = velocity;
	
	/*p.xi=20*(0.5f-rand()/static_cast<float>(RAND_MAX));
	p.yi=20*(0.5f-rand()/static_cast<float>(RAND_MAX));
	p.zi=20*(0.5f-rand()/static_cast<float>(RAND_MAX));*/

	//Set particle color
	this->r = r;
	this->g = g;
	this->b = b;
}

void Particle::Draw()
{
	if (isActive) 
	{
		glColor4f(r, g, b, life);

		glBegin(GL_QUADS);
		glTexCoord2d(1,1); glVertex3f(position.getX()+0.5f,position.getY()+0.5f,position.getZ()); // Top Right
		glTexCoord2d(0,1); glVertex3f(position.getX()-0.5f,position.getY()+0.5f,position.getZ()); // Top Left
		glTexCoord2d(0,0); glVertex3f(position.getX()-0.5f,position.getY()-0.5f,position.getZ()); // Bottom Left
		glTexCoord2d(1,0); glVertex3f(position.getX()+0.5f,position.getY()-0.5f,position.getZ()); // Bottom Right
		glEnd();
	}
}

void Particle::Update( GLfloat deltaTime )
{
	Drawable::CalculatePosition(deltaTime);
	life -= fade * deltaTime;

	if (life <= 0.0f) 
	{
		isActive=false;
	}
	else if(position.getZ() >= 10)
	{
		life = 0.0f;
		isActive = false;
	}
}

void Particle::CreateDrawable()
{
	isActive = false;
	life = 0.0f;
	fade = 0.0f;
	velocity = 0.0f;
	position = 0.0f;
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}
