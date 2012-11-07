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
	std::string boxPath = "..//skybox//"+ skyboxName + "//";
	skybox[SKY_LEFT]=loadTexture(boxPath + "left.png");
	skybox[SKY_BACK]=loadTexture(boxPath + "back.png");
	skybox[SKY_RIGHT]=loadTexture(boxPath + "right.png");
	skybox[SKY_FRONT]=loadTexture(boxPath + "front.png");
	skybox[SKY_TOP]=loadTexture(boxPath + "top.png");
	skybox[SKY_BOTTOM]=loadTexture(boxPath + "bottom.png");
	this->size = size;
}

void Skybox::drawSkybox()
{
	//checking if textures were turned on before enabling
	bool texIsEnabled; 
	if(glIsEnabled(GL_TEXTURE_2D))
		texIsEnabled = true;
	else texIsEnabled = false;
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);			
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]); 
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(size*-0.5f, size*-0.5f, size*-0.5f);//bottom left
	glTexCoord2f(0, 1);
	glVertex3f(size*0.5f, size*-0.5f, size*-0.5f);//bottom right
	glTexCoord2f(0, 0);
	glVertex3f(size*0.5f, size*0.5f, size*-0.5f); //top right
	glTexCoord2f(1, 0);
	glVertex3f(size*-0.5f, size*0.5f, size*-0.5f);//top left
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(size*-0.5f, size*-0.5f, size*0.5f);//front bottom
	glTexCoord2f(0, 1);
	glVertex3f(size*-0.5f, size*-0.5f, size*-0.5f);//back bottom
	glTexCoord2f(0, 0);
	glVertex3f(size*-0.5f, size*0.5f, size*-0.5f);//back top
	glTexCoord2f(1, 0);
	glVertex3f(size*-0.5f, size*0.5f, size*0.5f);//front top
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(size*-0.5f, size*-0.5f, size*0.5f);//bottom left
	glTexCoord2f(0, 0);
	glVertex3f(size*-0.5f, size*0.5f, size*0.5f);//top left
	glTexCoord2f(1, 0);
	glVertex3f(size*0.5f, size*0.5f, size*0.5f);//top right
	glTexCoord2f(1, 1);
	glVertex3f(size*0.5f, size*-0.5f, size*0.5f);//bottom right
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(size*0.5f, size*-0.5f, size*0.5f);//front bottom
	glTexCoord2f(0, 0);
	glVertex3f(size*0.5f, size*0.5f, size*0.5f);//front top
	glTexCoord2f(1, 0);
	glVertex3f(size*0.5f, size*0.5f, size*-0.5f);//back top
	glTexCoord2f(1, 1);
	glVertex3f(size*0.5f, size*-0.5f, size*-0.5f);//back bottom
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_TOP]);          
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(size*-0.5f, size*0.5f, size*0.5f);//front left
	glTexCoord2f(0, 0);
	glVertex3f(size*-0.5f, size*0.5f, size*-0.5f);//back left
	glTexCoord2f(1, 0);
	glVertex3f(size*0.5f, size*0.5f, size*-0.5f);//back right
	glTexCoord2f(1, 1);
	glVertex3f(size*0.5f, size*0.5f, size*0.5f);//front right
	
	
	glEnd();
	glPopMatrix();

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BOTTOM]);               
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(size*-0.5f, size*-0.5f, size*0.5f);//front left
	glTexCoord2f(1, 0);
	glVertex3f(size*0.5f, size*-0.5f, size*0.5f);//front right
	glTexCoord2f(1, 1);
	glVertex3f(size*0.5f, size*-0.5f, size*-0.5f);//back right
	glTexCoord2f(0, 1);
	glVertex3f(size*-0.5f, size*-0.5f, size*-0.5f);//back left
	glEnd();
	glPopMatrix();
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	if(!texIsEnabled)
		glDisable(GL_TEXTURE_2D);
}

unsigned int Skybox::loadTexture(std::string filename)
{
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
	
	return num;     //and we return the id
}

