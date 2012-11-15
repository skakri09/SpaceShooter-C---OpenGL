#include "TextureFactory.h"

TextureFactory::TextureFactory()
	:log("TextureFactory", WARN)
{

}

TextureFactory::~TextureFactory()
{

}

TextureFactory* TextureFactory::Inst()
{
	static TextureFactory* instance = new TextureFactory();
	return instance;
}

void TextureFactory::InitTextFactory()
{

}

GLuint TextureFactory::GetTexture( std::string textureName, std::string texturePath )
{
	if(Textures.find(textureName) != Textures.end())
	{
		return Textures.find(textureName)->second;
	}
	else
	{
		return LoadAndBindTexture(texturePath, textureName);
	}
}

GLuint TextureFactory::LoadAndBindTexture( std::string imageFullPathAndName, std::string keyName )
{
	Image* img = ReadImage(imageFullPathAndName);

	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	//Storing the texture in our map on the keyname
	Textures[keyName] = texId; 

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);      //we do it for vertically and horizontally (previous line)

	// Specify texture. If the image has four components, the last 
	// is the alpha channel, which we will use in the blending
	if (img->components == 3) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 
			0, GL_RGB, GL_UNSIGNED_BYTE, &img->data[0]);
	}
	else if (img->components == 4) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, &img->data[0]);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	if(img)
	{
		delete img;
		img = 0;
	}
	return texId;
}

Image* TextureFactory::ReadImage( std::string image )
{
	Image* img = new Image();
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
	}
	img->width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
	img->height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
	img->components = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	int memory_needed = img->width * img->height * img->components;
	img->data.resize(memory_needed); //Allocate memory

	// finally get the image data, and delete the il-image.
	if(img->components == 3)
	{
		ilCopyPixels(0, 0, 0, img->width, img->height, 1, IL_RGB, IL_UNSIGNED_BYTE, &img->data[0]);
	}
	else if(img->components == 4)
	{
		ilCopyPixels(0, 0, 0, img->width, img->height, 1, IL_RGBA, IL_UNSIGNED_BYTE, &img->data[0]);
	}

	ilDeleteImages(1, &imageName); 

	return img;
}

