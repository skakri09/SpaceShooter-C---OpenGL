#include "ParticleManager.h"

ParticleManager::ParticleManager()
	:log("ParticleManager", WARN)
{
	srand(time(0));

	zeroPoint.setX(0.0f);
	zeroPoint.setY(0.0f);
	zeroPoint.setZ(0.0f);
	failcounter= 0;
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

void ParticleManager::UpdateParticles( GLfloat deltatime)
{
	//Adding 3 new stars each frame until we are at the maximum number
	//This is just a simple way to avoid all the stars spawning at the
	//same time the first frame, which looks rather stupid. Instead we
	//spawn 1/10th of the stars the first frame, and then add another 3
	//each frame until we're at the max.
	if(LightspeedStars.size() < MAX_LIGHTPSEED_PARTICLES)
	{
		for(int i = 0; i < 5; i++)
		{
			Particle newParticle;
			LightspeedStars.push_back(newParticle);
		}
	}

	//Looping trough all particles and updating them if they are active. 
	//Are they not active we initialize them over again
	for(unsigned int i = 0; i < LightspeedStars.size(); i++)
	{
		if(LightspeedStars.at(i).isActive)
		{
			LightspeedStars.at(i).Update(deltatime);
		}
		else
		{
			InitNewLightspeedParticle(LightspeedStars.at(i), false);
		}
	}
}

void ParticleManager::DrawParticles()
{
	//Enabling Texture2ds for the particles only. Disabling it again after updating the particles.
	//It seems you can't draw polygons etc when texture2d is enabled. Maybe that changes when I 
	//put textures on the other models later.
	glEnable(GL_TEXTURE_2D);

	//Updating and drawing all LightspeedStars
	glBindTexture(GL_TEXTURE_2D, particle1);

	//Looping trough all the stars and drawing them if they are active
	for(unsigned int i = 0; i < LightspeedStars.size(); i++)
	{
		if(LightspeedStars.at(i).isActive)
		{
			LightspeedStars.at(i).Draw();
		}
	}

	glDisable(GL_TEXTURE_2D);
}

void ParticleManager::InitNewLightspeedParticle(Particle& p, bool firstFrame)
{
	Vector3D newParticlePos;
	Vector3D newParticleVel;
	
	/*float partOfScreen = GetRandFloat(0.0f, 4.0f);
	if(partOfScreen <= 1.0f)
	{

	}
	else if(partOfScreen <= 2.0f && partOfScreen > 1.0f)
	{

	}
	else if(partOfScreen <= 3.0f && partOfScreen > 2.0f)
	{

	}
	else
	{

	}*/

	float xPos = GetRandFloat(-MAX_STAR_DIST_FROM_MIDDLE_X, MAX_STAR_DIST_FROM_MIDDLE_X);
	float yPos = GetRandFloat(-MAX_STAR_DIST_FROM_MIDDLE_Y, MAX_STAR_DIST_FROM_MIDDLE_Y);
	
	//FAR FROM OPTIMAL OHMYGOD, maybe i'll fix l8r %)
	while(!validLightspeedPos(xPos, yPos))
	{
		xPos = GetRandFloat(-MAX_STAR_DIST_FROM_MIDDLE_X, MAX_STAR_DIST_FROM_MIDDLE_X);
		yPos = GetRandFloat(-MAX_STAR_DIST_FROM_MIDDLE_Y, MAX_STAR_DIST_FROM_MIDDLE_Y);
	}

	newParticlePos.setX(xPos);
	newParticlePos.setY(yPos);
	if(firstFrame)
	{
		newParticlePos.setZ(GetRandFloat(STAR_FARPOINT, 0));
	}
	else
	{
		newParticlePos.setZ(STAR_FARPOINT);
	}
	
	newParticleVel.setX(0.0f);
	newParticleVel.setY(0.0f);
	newParticleVel.setZ(10000/zeroPoint.Distance(newParticlePos, zeroPoint)*5);

	p.InitParticle(newParticlePos, newParticleVel, GetRandFloat(0.01f, 0.1f), 1, 1, 1);
}

bool ParticleManager::validLightspeedPos( float xPos, float yPos )
{
	if(xPos >FRUSTUM_LEFT && xPos < FRUSTUM_RIGHT)
	{
		if(yPos > FRUSTUM_BOTTOM && yPos < FRUSTUM_TOP)
		{
			failcounter++;
			log << INFO << failcounter << std::endl;
			return false;
			
		}
	}
	return true;
}

void ParticleManager::InitLightspeedStars()
{
	LightspeedStars.reserve(MAX_LIGHTPSEED_PARTICLES);
	LightspeedStars.resize(MAX_LIGHTPSEED_PARTICLES/10);
	for(unsigned int i = 0; i< LightspeedStars.size(); i++)
	{
		LightspeedStars.at(i).CreateDrawable();
		InitNewLightspeedParticle(LightspeedStars.at(i),true); 
		
	}
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
