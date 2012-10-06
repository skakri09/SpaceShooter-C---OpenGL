#include "ParticleManager.h"


#pragma region asd

ParticleManager::ParticleManager()
	:log("ParticleManager", WARN)
{
	srand(time(0));

	zeroPoint.setX(0.0f);
	zeroPoint.setY(0.0f);
	zeroPoint.setZ(0.0f);
}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::InitParticleManager()
{
	InitDevil();

	Image img = ReadImage("Particle.png");
	
	glGenTextures(1, &particle1);
	glBindTexture(GL_TEXTURE_2D, particle1);
	
	// Specify texture. If the image has four components, the last 
	// is the alpha channel, which we will use in the blending
	if (img.components == 3) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 
						0, GL_BGR_EXT, GL_UNSIGNED_BYTE, &img.data[0]);
	}
	else if (img.components == 4) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, 
						GL_BGRA_EXT, GL_UNSIGNED_BYTE, &img.data[0]);
	}

	//Set texture parameters for wrapping and minification/magnification filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Set that we want to use both the color of our geometry (i.e., glColor) and our texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	InitLightspeedStars();
}

void ParticleManager::UpdateAndDrawParticles( GLfloat deltatime )
{
	//Enabling Texture2ds for the particles only. Disabling it again after updating the particles.
	//It seems you can't draw polygons etc when texture2d is enabled. Maybe that changes when I 
	//put textures on the other models later.
	glEnable(GL_TEXTURE_2D);

	//Updating and drawing all LightspeedStars
	glBindTexture(GL_TEXTURE_2D, particle1);
	if(LightspeedStars.size() < MAX_LIGHTPSEED_PARTICLES)
	{
		Particle newParticle, newParticle2, newParticle3;
		LightspeedStars.push_back(newParticle);
		LightspeedStars.push_back(newParticle2);
		LightspeedStars.push_back(newParticle3);
	}
	for(unsigned int i = 0; i < LightspeedStars.size(); i++)
	{
		
		if(LightspeedStars.at(i).isActive)
		{
			LightspeedStars.at(i).UpdateParticle(deltatime);
			LightspeedStars.at(i).DrawParticle();
		}
		else
		{
			Vector3D newParticlePos;
			Vector3D newParticleVel;
			newParticlePos.setX(GetRandFloat(-MAX_STAR_DIST_FROM_MIDDLE_X, MAX_STAR_DIST_FROM_MIDDLE_X));
			newParticlePos.setY(GetRandFloat(-MAX_STAR_DIST_FROM_MIDDLE_Y, MAX_STAR_DIST_FROM_MIDDLE_Y));
			newParticlePos.setZ(STAR_FARPOINT);
			
			newParticleVel.setX(0.0f);
			newParticleVel.setY(0.0f);
			newParticleVel.setZ(10000/zeroPoint.Distance(newParticlePos, zeroPoint));

			LightspeedStars.at(i).InitParticle(newParticlePos, newParticleVel, GetRandFloat(0.01f, 0.1f), 1, 1, 1);
		}
	}
	glDisable(GL_TEXTURE_2D);
}


void ParticleManager::InitLightspeedStars()
{
	LightspeedStars.reserve(MAX_LIGHTPSEED_PARTICLES);
	LightspeedStars.resize(MAX_LIGHTPSEED_PARTICLES/10);
}

float ParticleManager::GetRandFloat( float min, float max )
{
	return ((max - min) * ((float)rand()/RAND_MAX))+min;
}

Image ParticleManager::ReadImage( std::string image )
{
	Image img;
	ILuint imageName; // The image name to return.
	ilGenImages(1, &imageName); // Grab a new image name.

	ilBindImage(imageName);
	
	if (!ilLoadImage(image.c_str()))
	{
		log << ERRORX << "Image: " << image << " not loaded correctly" << std::endl;
		ILenum Error;
		while ((Error = ilGetError()) != IL_NO_ERROR) {
			std::cout << Error << iluErrorString(Error) << std::endl;
		}
		ilDeleteImages(1, &imageName); // Delete the image name. 
		exit(-1);
	}
	img.width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
	img.height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
	img.components = 4;
	int memory_needed = img.width * img.height * img.components;
	img.data.resize(memory_needed); //Allocate memory

	// finally get the image data, and delete the il-image.
	ilCopyPixels(0, 0, 0, img.width, img.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, &img.data[0]);
	ilDeleteImages(1, &imageName); 

	return img;
}

void ParticleManager::InitDevil()
{
	// Initialize DevIL
	ilInit();
	iluInit();

	// Set the origin to be the lower left corner
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilEnable(IL_ORIGIN_SET);
}
#pragma endregion asd

/*
ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::init()
{
	initDevil(); //this may have to come first in gamemanager init()
	initParticles();

	// Enable texturing, loat texture from file, and generate a texture name
	glEnable(GL_TEXTURE_2D);
	Image img = readTexture("Particle.png");
	glGenTextures(1, &texName);

	// Create texture object
	glBindTexture(GL_TEXTURE_2D, texName);

	// Specify texture. If the image has four components, the last is the alpha channel, which we will use in the blending
	if (img.components == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, &img.data[0]);
	}
	else if (img.components == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, &img.data[0]);
	}

	//Set texture parameters for wrapping and minification/magnification filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Set that we want to use both the color of our geometry (i.e., glColor) and our texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void ParticleManager::render( GLfloat elapsed )
{
	//Set which texture we want to use
	glBindTexture(GL_TEXTURE_2D, texName);

	//Loop through all particles: update and draw
	for (int i=0; i<particles.size(); ++i) {
		updateParticle(particles[i], elapsed);
		drawParticle(particles[i]);
	}
}

void ParticleManager::initDevil()
{
	// Initialize DevIL
	ilInit();
	iluInit();

	// Set the origin to be the lower left corner
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilEnable(IL_ORIGIN_SET);
}

Image ParticleManager::readTexture( std::string image )
{
	Image img;
	ILuint imageName; // The image name to return.
	ilGenImages(1, &imageName); // Grab a new image name.

	ilBindImage(imageName); 

	if (!ilLoadImage(image.c_str())) {
		ILenum Error;
		while ((Error = ilGetError()) != IL_NO_ERROR) {
			std::cout << Error << iluErrorString(Error) << std::endl;
		}
		ilDeleteImages(1, &imageName); // Delete the image name. 
		exit(-1);
	}
	img.width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
	img.height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
	img.components = 4;
	int memory_needed = img.width * img.height * img.components;
	img.data.resize(memory_needed); //Allocate memory

	// finally get the image data, and delete the il-image.
	ilCopyPixels(0, 0, 0, img.width, img.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, &img.data[0]);
	ilDeleteImages(1, &imageName); 

	return img;
}

void ParticleManager::initParticles()
{
	particles.resize(max_particles);
	for (int i=0;i<particles.size();++i) {
		initParticle(particles.at(i));
	}
}

void ParticleManager::updateParticle( Particle& p, double elapsed )
{
	p.x += p.xi*elapsed;// Move On The X Axis By X Speed
	p.y += p.yi*elapsed;// Move On The Y Axis By Y Speed
	p.z += p.zi*elapsed;// Move On The Z Axis By Z Speed

	p.life -= p.fade*elapsed;

	if (p.life <= 0.0f) {
		p.active=false;
	}
}

void ParticleManager::drawParticle( const Particle& p )
{
	if (p.active) {
		// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
		glColor4f(p.r, p.g, p.b, p.life);

		glBegin(GL_QUADS);
		glTexCoord2d(1,1); glVertex3f(p.x+0.5f,p.y+0.5f,p.z); // Top Right
		glTexCoord2d(0,1); glVertex3f(p.x-0.5f,p.y+0.5f,p.z); // Top Left
		glTexCoord2d(0,0); glVertex3f(p.x-0.5f,p.y-0.5f,p.z); // Bottom Left
		glTexCoord2d(1,0); glVertex3f(p.x+0.5f,p.y-0.5f,p.z); // Bottom Right
		glEnd();
	}
}

void ParticleManager::initParticle( Particle& p )
{
	p.active=true;								// Make All The Particles Active
	p.life=1.0f;								// Give All The Particles Full Life
	p.fade=rand()/static_cast<float>(RAND_MAX)+0.1f;	// Random Fade Speed

	//Set particle initial position
	p.x=0.0f;
	p.y=0.0f;
	p.z=0.0f;

	//Set speeds for this particle
	p.xi=20*(0.5f-rand()/static_cast<float>(RAND_MAX));
	p.yi=20*(0.5f-rand()/static_cast<float>(RAND_MAX));
	p.zi=20*(0.5f-rand()/static_cast<float>(RAND_MAX));

	//Set particle color
	p.r = 1.0;
	p.g = 0.5;
	p.b = 0.5;
}
*/