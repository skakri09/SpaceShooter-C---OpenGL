#include "Texturable.h"


Texturable::Texturable()
	:log("Texturable", WARN)
{
}

Texturable::~Texturable()
{
}

void Texturable::BindTexture(std::string textureName)
{
	glEnable(GL_TEXTURE_2D);
	if(textures.find(textureName) != textures.end())
	{
		glBindTexture(GL_TEXTURE_2D, textures.find(textureName)->second);
	}
	else
	{
		log << ERRORX << textureName << " not bound, it has not been created." << std::endl;
		log << ERRORX << "Attempting to load and bind it..." << std::endl;
	}
}

void Texturable::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}


void Texturable::InitTexture( std::string textureFullPathname, std::string textureKeyName )
{

}

void Texturable::LoadAndBindTexture( std::string imageFullPathAndName, std::string keyName )
{
	Image img = ReadImage(imageFullPathAndName);

	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	
	//Storing the texture in our map on the keyname
	textures[keyName] = texId; 

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

	glBindTexture(GL_TEXTURE_2D, 0);
}

Image Texturable::ReadImage( std::string image )
{
	Image img;
	ILuint imageName; // The image name to return.
	ilGenImages(1, &imageName); // Grab a new image name.

	ilBindImage(imageName);

	if (!ilLoadImage(image.c_str()))
	{
		log << ERRORX << "Image: " << image << " not loaded correctly" << std::endl;
		ILenum Error;
		while ((Error = ilGetError()) != IL_NO_ERROR) 
		{
			log << ERRORX << Error << iluErrorString(Error) << std::endl;
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

