#include "ImageEntry.h"


ImageEntry::ImageEntry(std::string textureName, float xPos, float yPos, float zPos, float scale)
{
	
	this->textureName = textureName;
	this->texturePath = "..//images//" + textureName;
	GUIEntry::transformable.Init(xPos, yPos, zPos, Vector3D::ZeroVec(), scale, Vector3D::ZeroVec());
}


ImageEntry::~ImageEntry()
{

}

void ImageEntry::Init()
{
	std::string texPath = "..//images//";
	texPath += textureName;
	this->textureName = textureName;
	texture.InitTexture(texPath, textureName);
	_vbo.SetMeshInfo(MeshFactory::Inst()->GetMesh("..//xml//square.xml"));
}

void ImageEntry::Draw( VBODrawable* vbo )
{
	glPushMatrix();
	texture.BindTexture(textureName);
	GUIEntry::transformable.ApplyGLTransformations(true, true, false);
	_vbo.Draw();
	glPopMatrix();
}

