#include "Skybox.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;

Skybox::Skybox() :log("Skybox", WARN)
{
}

Skybox::~Skybox()
{
}

void Skybox::initSkybox(std::string skyboxName, float size)
{
	tex.InitTexture("..//skybox//skybox1//all.png", "skybox1");

	std::string boxPath = "..//skybox//"+ skyboxName + "//";
	spaceBox[SKY_LEFT]=loadTexture(boxPath + "left.png");
	spaceBox[SKY_BACK]=loadTexture(boxPath + "back.png");
	spaceBox[SKY_RIGHT]=loadTexture(boxPath + "right.png");
	spaceBox[SKY_FRONT]=loadTexture(boxPath + "front.png");
	spaceBox[SKY_TOP]=loadTexture(boxPath + "top.png");
	spaceBox[SKY_BOTTOM]=loadTexture(boxPath + "bottom.png");
	this->size = size;
	rotate = 0.0f;
	vbo.SetMeshInfo(MeshFactory::Inst()->GetMesh("..//xml//skybox1.xml"));
}

void Skybox::drawSkybox()
{
	
	glPushMatrix();

	glScaled(size, size, size);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);

	tex.BindTexture("skybox1");
	vbo.Draw();
	tex.UnbindTexture();

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glClear(GL_DEPTH_BUFFER_BIT);
}

unsigned int Skybox::loadTexture(std::string filename)
{
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
	Image img;
	unsigned int num;       //the id for the texture
	
	glGenTextures(1,&num);  //we generate a unique one
	ILuint imageName; // The image name to return.
	ilGenImages(1, &imageName); // Grab a new image name.

	ilBindImage(imageName);

	if (!ilLoadImage(filename.c_str()))
	{
		log << ERRORX << "Image: " << filename << " not loaded correctly" << std::endl;
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
	
	glBindTexture(GL_TEXTURE_2D,num);       //and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);      //we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img.width,img.height,0,GL_RGBA,IL_UNSIGNED_BYTE,&img.data[0]);        //we make the actual texture
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	return num;     //and we return the id
}

void Skybox::UpdateSkybox( float deltaTime )
{
	rotate += deltaTime*1.5f;
	if(rotate >= 360)
	{
		rotate -=360;
	}
}

