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
	loadedSkybox = skyboxName;
	std::string path = "..//skybox//" + skyboxName + "//skybox.jpg";
	tex.InitTexture(path, skyboxName);
	this->size = size;
	rotate = 0.0f;
	vbo.SetMeshInfo(MeshFactory::Inst()->GetMesh("..//xml//skybox.xml"));
}

void Skybox::drawSkybox()
{
	glPushMatrix();

	glScaled(size, size, size);

	glDisable(GL_LIGHTING);

	tex.BindTexture(loadedSkybox);
	vbo.Draw();
	tex.UnbindTexture();

	glEnable(GL_LIGHTING);
	glPopMatrix();

	glClear(GL_DEPTH_BUFFER_BIT);
}

void Skybox::UpdateSkybox( float deltaTime )
{
	rotate += deltaTime*1.5f;
	if(rotate >= 360)
	{
		rotate -=360;
	}
}

