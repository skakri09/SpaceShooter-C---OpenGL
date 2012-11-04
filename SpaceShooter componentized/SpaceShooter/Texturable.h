/********************************************************************
    created:    4:11:2012   18:39
    filename:   Texturable.h
    author:     Kristian Skarseth
    
    purpose:    A component giving functionality to load and bind textures
*********************************************************************/
#ifndef Texturable_h__
#define Texturable_h__

#ifdef _WIN32
#include <windows.h>
#endif

#include <IL/il.h>
#include <IL/ilu.h>
#include <map>

#include "Image.h"
#include "Logger.h"

#include <gl/glew.h>
#include <gl/GL.h>

class Texturable
{
public:
    Texturable();
    ~Texturable();

	void InitTexture(std::string textureFullPathname, std::string textureKeyName);


protected:
	void BindTexture(std::string textureName);
	void UnbindTexture();

	void LoadAndBindTexture(std::string imageFullPathAndName, std::string keyName);

private:
	Logger log;

	std::map<std::string, GLuint> textures;

	

	Image ReadImage(std::string image);


};

#endif // Texturable_h__