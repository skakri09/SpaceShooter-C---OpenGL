#include "Texturable.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;

Texturable::Texturable()
	:log("Texturable", WARN)
{
}

Texturable::~Texturable()
{
}

void Texturable::BindTexture(std::string textureName)
{
	glEnable(GL_TEXTURE_2D);
	if(textures.find(textureName) != textures.end())
	{
		glBindTexture(GL_TEXTURE_2D, textures.find(textureName)->second);
	}
	else
	{
		log << ERRORX << textureName << " not bound, it has not been created." << std::endl;
	}
}

void Texturable::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}


void Texturable::InitTexture( std::string textureFullPathname, std::string textureKeyName )
{
	if(textures.find(textureKeyName) == textures.end())
	{
		textures[textureKeyName] = TextureFactory::Inst()->GetTexture(textureKeyName, textureFullPathname);
	}
}
