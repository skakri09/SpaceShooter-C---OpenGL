/********************************************************************
    created:    28:10:2012   11:16
    filename:   Skybox.h
    author:     Kristian Skarseth
    
    purpose:    Class to draw a desired skybox
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
#include <vector>

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

	void initSkybox(std::string skyboxName, float size);

	void drawSkybox();

	unsigned int skybox[6];

	float size;

private:
	Logger log;

	unsigned int loadTexture(std::string filename);
};

#endif // Skybox_h__