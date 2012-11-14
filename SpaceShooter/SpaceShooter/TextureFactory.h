/********************************************************************
    created:    14:11:2012   23:23
    filename:   TextureFactory.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef TextureFactory_h__
#define TextureFactory_h__

#include <string>
#include <map>
#include <gl/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>

#include "Image.h"
#include "Logger.h"

class TextureFactory
{
public:
    static TextureFactory* Inst();

	void InitTextFactory();

	GLuint GetTexture(std::string textureName, std::string texturePath);

protected:

private:
	TextureFactory();
	~TextureFactory();

	Logger log;

	std::map<std::string, GLuint> Textures;

	GLuint LoadAndBindTexture(std::string imageFullPathAndName, std::string keyName);

	Image* ReadImage(std::string image);
};

#endif // TextureFactory_h__