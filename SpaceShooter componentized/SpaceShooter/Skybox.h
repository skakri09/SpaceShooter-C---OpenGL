/********************************************************************
    created:    28:10:2012   11:16
    filename:   Skybox.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Skybox_h__
#define Skybox_h__

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/glew.h>
#include <string>
#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>

#include "Image.h"
#include "Logger.h"
enum faces{SKY_LEFT=0, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM};

struct ImageProperties
{
	unsigned long width;
	unsigned long height;
};
class Skybox
{
public:
    Skybox();
    ~Skybox();

	void initSkybox();

	void drawSkybox();

	unsigned int loadTexture(const char* filename);

	unsigned int skybox[6];

private:
	Logger log;
	/*void InitSkybox(std::string skyBoxName, std::string extension);

	void DrawSkybox(float size);

	void createCubeMap();
	void drawCube(float size);

	void drawCubeBox(float size);
private:
	

	GLuint skybox[6];

	GLuint LoadImage(std::string image);

	Image readTexture(std::string image);
	void drawQuad(float size);
	
	GLuint texName;*/
};

#endif // Skybox_h__