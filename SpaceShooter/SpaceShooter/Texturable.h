/********************************************************************
    created:    4:11:2012   18:39
    filename:   Texturable.h
    author:     Kristian Skarseth
    
    purpose:    A component giving functionality to load and bind textures.
				Not entirely finished yet.
*********************************************************************/
#ifndef Texturable_h__
#define Texturable_h__

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <map>

#include "Image.h"
#include "Logger.h"

#include "TextureFactory.h"

class Texturable
{
public:
    Texturable();
    ~Texturable();

	void InitTexture(std::string textureFullPathname, std::string textureKeyName);

	void BindTexture(std::string textureName);
	void UnbindTexture();

private:
	Logger log;

	std::map<std::string, GLuint> textures;

};

#endif // Texturable_h__