#include "Skybox.h"


Skybox::Skybox() :log("Skybox", WARN)
{
}

Skybox::~Skybox()
{
}

void Skybox::initSkybox()
{
	skybox[SKY_LEFT]=loadTexture("..//skybox//skybox1//left.png");
	skybox[SKY_BACK]=loadTexture("..//skybox//skybox1//back.png");
	skybox[SKY_RIGHT]=loadTexture("..//skybox//skybox1//right.png");
	skybox[SKY_FRONT]=loadTexture("..//skybox//skybox1//front.png");
	skybox[SKY_TOP]=loadTexture("..//skybox//skybox1//top.png");
	skybox[SKY_BOTTOM]=loadTexture("..//skybox//skybox1//bottom.png");
	size = 200;
}

void Skybox::drawSkybox()
{
	bool b1=glIsEnabled(GL_TEXTURE_2D);     //new, we left the textures turned on, if it was turned on
	glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);       //turn off depth texting
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_CULL_FACE);
	
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
	
	//and turn on texturing
	//glDisable(GL_CULL_FACE);
	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);  //use the texture we want
	//glBegin(GL_QUADS);      //and draw a face
	////back face
	//glTexCoord2f(0,0);      //use the correct texture coordinate
	//glVertex3f(size/2,size/2,size/2);       //and a vertex
	//glTexCoord2f(1,0);      //and repeat it...
	//glVertex3f(-size/2,size/2,size/2);
	//glTexCoord2f(1,1);
	//glVertex3f(-size/2,-size/2,size/2);
	//glTexCoord2f(0,1);
	//glVertex3f(size/2,-size/2,size/2);
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
	//glBegin(GL_QUADS);     
	////left face
	//glTexCoord2f(0,0);
	//glVertex3f(-size/2,size/2,size/2);
	//glTexCoord2f(1,0);
	//glVertex3f(-size/2,size/2,-size/2);
	//glTexCoord2f(1,1);
	//glVertex3f(-size/2,-size/2,-size/2);
	//glTexCoord2f(0,1);
	//glVertex3f(-size/2,-size/2,size/2);
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
	//glBegin(GL_QUADS);     
	////front face
	//glTexCoord2f(1,0);
	//glVertex3f(size/2,size/2,-size/2);
	//glTexCoord2f(0,0);
	//glVertex3f(-size/2,size/2,-size/2);
	//glTexCoord2f(0,1);
	//glVertex3f(-size/2,-size/2,-size/2);
	//glTexCoord2f(1,1);
	//glVertex3f(size/2,-size/2,-size/2);
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
	//glBegin(GL_QUADS);     
	////right face
	//glTexCoord2f(0,0);
	//glVertex3f(size/2,size/2,-size/2);
	//glTexCoord2f(1,0);
	//glVertex3f(size/2,size/2,size/2);
	//glTexCoord2f(1,1);
	//glVertex3f(size/2,-size/2,size/2);
	//glTexCoord2f(0,1);
	//glVertex3f(size/2,-size/2,-size/2);
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_TOP]);          
	//glBegin(GL_QUADS);                      //top face
	//glTexCoord2f(1,0);
	//glVertex3f(size/2,size/2,size/2);
	//glTexCoord2f(0,0);
	//glVertex3f(-size/2,size/2,size/2);
	//glTexCoord2f(0,1);
	//glVertex3f(-size/2,size/2,-size/2);
	//glTexCoord2f(1,1);
	//glVertex3f(size/2,size/2,-size/2);
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_BOTTOM]);               
	//glBegin(GL_QUADS);     
	////bottom face
	//glTexCoord2f(1,1);
	//glVertex3f(size/2,-size/2,size/2);
	//glTexCoord2f(0,1);
	//glVertex3f(-size/2,-size/2,size/2);
	//glTexCoord2f(0,0);
	//glVertex3f(-size/2,-size/2,-size/2);
	//glTexCoord2f(1,0);
	//glVertex3f(size/2,-size/2,-size/2);
	//glEnd();
	
	
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
	glEnable(GL_DEPTH_TEST);
	if(!b1)
		glDisable(GL_TEXTURE_2D);
}

unsigned int Skybox::loadTexture(const char* filename)
{
	Image img;
	unsigned int num;       //the id for the texture
	
	glGenTextures(1,&num);  //we generate a unique one
	ILuint imageName; // The image name to return.
	ilGenImages(1, &imageName); // Grab a new image name.

	ilBindImage(imageName);

	if (!ilLoadImage(filename))
		//if (!ilLoad(IL_PNG, image.c_str()))
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


void Skybox::CreateSkyBox(float x, float y, float z, float width, float height, float length)
{
	/*
		All this function does is create 6 squares and distance them according to the measurements 
			provided by the user. Mess around with it if you want.
	*/

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_BACK]);

	// Center the skybox
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z);
		
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_FRONT]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z + length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox[SKY_BOTTOM]);
	glBegin(GL_QUADS);		
	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_TOP]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height,	z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_LEFT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height,	z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);		
		
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_RIGHT]);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,	z + length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,	z);
	glEnd();
}

void Skybox::drawQuad()
{
	glBegin(GL_QUADS);

	//glNormal3f(0.0f, 0.0f, 1.0f);
	//back face
	//glTexCoord2f(0,0);      //use the correct texture coordinate
	glTexCoord2f(1,1);      //use the correct texture coordinate
	glVertex3f(size*0.5f, size*0.5f,size* -0.5f);//top right
	//glVertex3f(size/2,size/2,size/2);       //top right
	
	//glTexCoord2f(1,0);      //and repeat it...
	glTexCoord2f(0,1);      //and repeat it...
	glVertex3f(size*-0.5f, size*0.5f, size*-0.5f);//top left
	//glVertex3f(-size/2,size/2,size/2);//topleft
	
	//glTexCoord2f(1,1);
	glTexCoord2f(0,0);
	glVertex3f(size*-0.5f, size*-0.5f, size*-0.5f);//bottom left
	//glVertex3f(-size/2,-size/2,size/2);//bottomleft
	
	//glTexCoord2f(0,1);
	glTexCoord2f(1,0);
	glVertex3f(size*0.5f, size*-0.5f, size*-0.5f);//bottom right
	//glVertex3f(size/2,-size/2,size/2);//bottomright	
	glEnd();
}

//void Skybox::DrawSkybox(float size)
//{
//	bool b1=glIsEnabled(GL_TEXTURE_2D);     //new, we left the textures turned on, if it was turned on
//	glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
//	glDisable(GL_DEPTH_TEST);       //turn off depth texting
//	glEnable(GL_TEXTURE_2D);        //and turn on texturing
//	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);  //use the texture we want
//	//glBegin(GL_QUADS);      //and draw a face
//	////back face
//	//glTexCoord2f(0,0);      //use the correct texture coordinate
//	//glVertex3f(size/2,size/2,size/2);       //and a vertex
//	//glTexCoord2f(1,0);      //and repeat it...
//	//glVertex3f(-size/2,size/2,size/2);
//	//glTexCoord2f(1,1);
//	//glVertex3f(-size/2,-size/2,size/2);
//	//glTexCoord2f(0,1);
//	//glVertex3f(size/2,-size/2,size/2);
//	//glEnd();
//	glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
//	glBegin(GL_QUADS);     
//	//left face
//	glTexCoord2f(0,0);
//	glVertex3f(-size/2,size/2,size/2);
//	glTexCoord2f(1,0);
//	glVertex3f(-size/2,size/2,-size/2);
//	glTexCoord2f(1,1);
//	glVertex3f(-size/2,-size/2,-size/2);
//	glTexCoord2f(0,1);
//	glVertex3f(-size/2,-size/2,size/2);
//	glEnd();
//	glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
//	glBegin(GL_QUADS);     
//	//front face
//	glTexCoord2f(1,0);
//	glVertex3f(size/2,size/2,-size/2);
//	glTexCoord2f(0,0);
//	glVertex3f(-size/2,size/2,-size/2);
//	glTexCoord2f(0,1);
//	glVertex3f(-size/2,-size/2,-size/2);
//	glTexCoord2f(1,1);
//	glVertex3f(size/2,-size/2,-size/2);
//	glEnd();
//	glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
//	glBegin(GL_QUADS);     
//	//right face
//	glTexCoord2f(0,0);
//	glVertex3f(size/2,size/2,-size/2);
//	glTexCoord2f(1,0);
//	glVertex3f(size/2,size/2,size/2);
//	glTexCoord2f(1,1);
//	glVertex3f(size/2,-size/2,size/2);
//	glTexCoord2f(0,1);
//	glVertex3f(size/2,-size/2,-size/2);
//	glEnd();
//	glBindTexture(GL_TEXTURE_2D,skybox[SKY_TOP]);          
//	glBegin(GL_QUADS);                      //top face
//	glTexCoord2f(1,0);
//	glVertex3f(size/2,size/2,size/2);
//	glTexCoord2f(0,0);
//	glVertex3f(-size/2,size/2,size/2);
//	glTexCoord2f(0,1);
//	glVertex3f(-size/2,size/2,-size/2);
//	glTexCoord2f(1,1);
//	glVertex3f(size/2,size/2,-size/2);
//	glEnd();
//	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BOTTOM]);               
//	glBegin(GL_QUADS);     
//	//bottom face
//	glTexCoord2f(1,1);
//	glVertex3f(size/2,-size/2,size/2);
//	glTexCoord2f(0,1);
//	glVertex3f(-size/2,-size/2,size/2);
//	glTexCoord2f(0,0);
//	glVertex3f(-size/2,-size/2,-size/2);
//	glTexCoord2f(1,0);
//	glVertex3f(size/2,-size/2,-size/2);
//	glEnd();
//	glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
//	glEnable(GL_DEPTH_TEST);
//	if(!b1)
//		glDisable(GL_TEXTURE_2D);
//}
//
//void Skybox::InitSkybox(std::string skyBoxName, std::string extension)
//{
//	std::string basePath = "..//skybox//";
//	basePath+=skyBoxName+"//";
//
//	skybox[SKY_LEFT] = LoadImage(basePath+"left"+extension);
//	skybox[SKY_BACK] = LoadImage(basePath+"back"+extension);
//	skybox[SKY_RIGHT] = LoadImage(basePath+"right"+extension);
//	skybox[SKY_FRONT] = LoadImage(basePath+"front"+extension);
//	skybox[SKY_TOP] = LoadImage(basePath+"top"+extension);
//	skybox[SKY_BOTTOM] = LoadImage(basePath+"bottom"+extension);
//
//
//	//glEnable(GL_TEXTURE_CUBE_MAP_EXT);
//
//	////Generate texture id and texture object
//	//glGenTextures(1, &texName);
//	//glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, texName);
//
//	////Upload the six faces
//	//for (int i=0; i<6; ++i) {
//	//	Image img = readTexture(faceFilenames[i]);
//	//	glTexImage2D(faceTarget[i], 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &img.data[0]);
//	//}
//}
//
//static const char* faceFilenames[6] = {
//	"..//skybox//skybox1//right.png", 
//	"..//skybox//skybox1//left.png", 
//	"..//skybox//skybox1//top.png", 
//	"..//skybox//skybox1//bottom.png", 
//	"..//skybox//skybox1//front.png", 
//	"..//skybox//skybox1//back.png"
//};
//
//static GLenum faceTarget[6] = {
//	GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT,
//	GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT,
//	GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT,
//	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT,
//	GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT,
//	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT
//};
//GLuint Skybox::LoadImage( std::string image )
//{
//	Image img;
//
//	ILuint imageName; // The image name to return.
//	ilGenImages(1, &imageName); // Grab a new image name.
//
//	ilBindImage(imageName);
//
//	if (!ilLoadImage(image.c_str()))
//	//if (!ilLoad(IL_PNG, image.c_str()))
//	{
//		log << ERRORX << "Image: " << image << " not loaded correctly" << std::endl;
//		ILenum Error;
//		while ((Error = ilGetError()) != IL_NO_ERROR) {
//			std::cout << Error << iluErrorString(Error) << std::endl;
//		}
//		ilDeleteImages(1, &imageName); // Delete the image name. 
//		exit(-1);
//	}
//	img.width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
//	img.height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
//	img.components = 4;
//	int memory_needed = img.width * img.height * img.components;
//	img.data.resize(memory_needed); //Allocate memory
//
//	// finally get the image data, and delete the il-image.
//	ilCopyPixels(0, 0, 0, img.width, img.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, &img.data[0]);
//	ilDeleteImages(1, &imageName); 
//
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//
//	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
//	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
//	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
//	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);	//we do it for vertically and horizontally (previous line)
//	//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width,img.height,0,GL_RGBA,GL_UNSIGNED_BYTE, &img.data[0]);	
//	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width,img.height,0,GL_RGBA,GL_UNSIGNED_BYTE, &img.data[0]);
//	return textureID;
//}
//
//void Skybox::createCubeMap()
//{
//	glEnable(GL_TEXTURE_CUBE_MAP_EXT);
//
//	//Generate texture id and texture object
//	glGenTextures(1, &texName);
//	glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, texName);
//
//	//Upload the six faces
//	for (int i=0; i<6; ++i) {
//		Image img = readTexture(faceFilenames[i]);
//		glTexImage2D(faceTarget[i], 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &img.data[0]);
//	}
//
//	//Set texture parameters for wrapping and minification/magnification filters
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	//Set how we should generate texture coordinates
//	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
//	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
//	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
//
//	//Set that we want to generate texture coordinates
//	glEnable(GL_TEXTURE_GEN_S);
//	glEnable(GL_TEXTURE_GEN_T);
//	glEnable(GL_TEXTURE_GEN_R);
//
//	//Set that we want to use only the texture color
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//}
//
//void Skybox::drawQuad(float size)
//{
//	float x = size*-0.5f;
//	glBegin(GL_QUADS);
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(size*0.5f, size*-0.5f, size*0.5f);
//	glVertex3f(size*0.5f, size*0.5f, size*0.5f);
//	glVertex3f(size*-0.5f, size*0.5f, size*0.5f);
//	glVertex3f(size*-0.5f, size*-0.5f, size*0.5f);
//	glEnd();
//}
//
//void Skybox::drawCube(float size)
//{
//	drawQuad(size);
//	glRotatef(90, 1, 0, 0);
//	drawQuad(size);
//	glRotatef(90, 1, 0, 0);
//	drawQuad(size);
//	glRotatef(90, 1, 0, 0);
//	drawQuad(size);
//	glRotatef(90, 0, 1, 0);
//	drawQuad(size);
//	glRotatef(180, 0, 1, 0);
//	drawQuad(size);
//}
//
//Image Skybox::readTexture( std::string image )
//{
//	Image img;
//	ILuint imageName; // The image name to return.
//	ilGenImages(1, &imageName); // Grab a new image name.
//
//	ilBindImage(imageName); 
//
//	if (!ilLoadImage(image.c_str())) {
//		ILenum Error;
//		while ((Error = ilGetError()) != IL_NO_ERROR) {
//			std::cout << Error << iluErrorString(Error) << std::endl;
//		}
//		ilDeleteImages(1, &imageName); // Delete the image name. 
//		exit(-1);
//	}
//	img.width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
//	img.height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
//	img.components = 4;
//	int memory_needed = img.width * img.height * img.components;
//	img.data.resize(memory_needed); //Allocate memory
//
//	// finally get the image data, and delete the il-image.
//	ilCopyPixels(0, 0, 0, img.width, img.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, &img.data[0]);
//	ilDeleteImages(1, &imageName); 
//
//	return img;
//}
//
//void Skybox::drawCubeBox(float size)
//{
//	// Store the current matrix
//	glPushMatrix();
//
//	// Reset and transform the matrix.
//	glLoadIdentity();
//	//gluLookAt(
//	//	0,0,0,
//	//	camera->x(),camera->y(),camera->z(),
//	//	0,1,0);
//
//	// Enable/Disable features
//	glPushAttrib(GL_ENABLE_BIT);
//	glEnable(GL_TEXTURE_2D);
//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_LIGHTING);
//	glDisable(GL_BLEND);
//
//	// Just in case we set all vertices to white.
//	glColor4f(1,1,1,1);
//
//	//// Render the front quad
//	//glBindTexture(GL_TEXTURE_2D, skybox[SKY_FRONT]);
//	//glBegin(GL_QUADS);
//	//glTexCoord2f(0, 0); glVertex3f(  size*0.5f, size*-0.5f, size*-0.5f );
//	//glTexCoord2f(1, 0); glVertex3f( size*-0.5f, size*-0.5f, size*-0.5f );
//	//glTexCoord2f(1, 1); glVertex3f(size* -0.5f, size* 0.5f, size*-0.5f );
//	//glTexCoord2f(0, 1); glVertex3f( size* 0.5f,  size*0.5f, size*-0.5f );
//	//glEnd();
//
//	// Render the left quad
//	glBindTexture(GL_TEXTURE_2D, skybox[SKY_LEFT]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0); glVertex3f( size* 0.5f, size*-0.5f, size* 0.5f );
//	glTexCoord2f(1, 0); glVertex3f(  size*0.5f, size*-0.5f, size*-0.5f );
//	glTexCoord2f(1, 1); glVertex3f( size* 0.5f, size* 0.5f, size*-0.5f );
//	glTexCoord2f(0, 1); glVertex3f( size* 0.5f, size* 0.5f, size* 0.5f );
//	glEnd();
//
//	//// Render the back quad
//	//glBindTexture(GL_TEXTURE_2D, skybox[SKY_BACK]);
//	//glBegin(GL_QUADS);
//	//glTexCoord2f(0, 0); glVertex3f( size*-0.5f, size*-0.5f, size* 0.5f );
//	//glTexCoord2f(1, 0); glVertex3f( size* 0.5f, size*-0.5f, size* 0.5f );
//	//glTexCoord2f(1, 1); glVertex3f( size* 0.5f,  size*0.5f, size* 0.5f );
//	//glTexCoord2f(0, 1); glVertex3f( size*-0.5f,  size*0.5f, size* 0.5f );
//
//	//glEnd();
//
//	//// Render the right quad
//	//glBindTexture(GL_TEXTURE_2D, skybox[SKY_RIGHT]);
//	//glBegin(GL_QUADS);
//	//glTexCoord2f(0, 0); glVertex3f( size*-0.5f, size* -0.5f, size* -0.5f );
//	//glTexCoord2f(1, 0); glVertex3f( size*-0.5f,size* -0.5f,size*  0.5f );
//	//glTexCoord2f(1, 1); glVertex3f( size*-0.5f,size*  0.5f, size* 0.5f );
//	//glTexCoord2f(0, 1); glVertex3f( size* -0.5f,size*  0.5f, size*-0.5f );
//	//glEnd();
//
//	//// Render the top quad
//	//glBindTexture(GL_TEXTURE_2D, skybox[SKY_TOP]);
//	//glBegin(GL_QUADS);
//	//glTexCoord2f(0, 1); glVertex3f( size*-0.5f, size* 0.5f,size* -0.5f );
//	//glTexCoord2f(0, 0); glVertex3f( size*-0.5f, size* 0.5f,size*  0.5f );
//	//glTexCoord2f(1, 0); glVertex3f( size* 0.5f, size* 0.5f,size*  0.5f );
//	//glTexCoord2f(1, 1); glVertex3f( size* 0.5f,size* 0.5f, size*-0.5f );
//	//glEnd();
//
//	// Render the bottom quad
//	glBindTexture(GL_TEXTURE_2D, skybox[SKY_BOTTOM]);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0); glVertex3f( size*-0.5f,size* -0.5f,size* -0.5f );
//	glTexCoord2f(0, 1); glVertex3f( size*-0.5f, size*-0.5f,size*  0.5f );
//	glTexCoord2f(1, 1); glVertex3f(size*  0.5f,size* -0.5f,size*  0.5f );
//	glTexCoord2f(1, 0); glVertex3f( size* 0.5f, size*-0.5f, size*-0.5f );
//	glEnd();
//
//	// Restore enable bits and matrix
//	glPopAttrib();
//	glPopMatrix();
//}
//
