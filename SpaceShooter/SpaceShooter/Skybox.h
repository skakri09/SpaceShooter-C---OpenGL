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
#include "VBODrawable.h"
#include "MeshFactory.h"
#include "Texturable.h"

class Skybox
{
public:
    Skybox();
    ~Skybox();

	void initSkybox(std::string skyboxName, float size);

	void drawSkybox();

	void UpdateSkybox(float deltaTime);

private:
	float size;
	float rotate;

	VBODrawable vbo;
	Texturable tex;

	std::string loadedSkybox;
	Logger log;

};

#endif // Skybox_h__