/********************************************************************
    created:    5:10:2012   14:26
    filename:   Particle.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Particle_h__
#define Particle_h__

#ifdef _WIN32
#include <windows.h>
#endif

#include "VBODrawable.h"
#include "Transformable.h"
#include "GameObject.h"
#include <vector>
#include "Vector3d.h"
#include "MeshFactory.h"
#include "Image.h"

#include <gl/GL.h>



class Particle : public GameObject
{
public:
    Particle();
    virtual ~Particle();

	virtual void Draw();
	
	virtual void Update(GLfloat deltaTime);

	void InitParticle(Vector3D StartPos, Vector3D Velocity, float lifeDuration, 
						float r, float g, float b, float scale = 1.0f);
	
	float life;  //The life of the particle
	float fade;  //The fade speed of the particle (fade value is subtracted from life)
	
	float r;     //Red color value
	float g;	 //Green color value
	float b;	 //Blue color value

	VBODrawable vbo;				//We draw particles with VBOs
	Transformable transformation;	//We can transform particles

protected:

private:
	void CreateParticle(std::string particleNameNoExtension);

	Image ReadImage(std::string particleName);

};

#endif // Particle_h__